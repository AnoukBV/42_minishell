/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:00:48 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/04 11:30:41 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	protect_new_size(char *exp)
{
	int		size;
	size_t	i;
	t_esc	stat;
	t_esc	save;

	size = 0;
	i = 0;
	stat.is_quoted = false;
	while (exp[i])
	{
		check_quote(&stat, &exp[i]);
		if (exp[i] == '\'' && stat.is_quoted == true)
			size += 2;
		else if (exp[i] == '"' && stat.is_quoted == true)
			size += 2;
		else if (exp[i] == '"' && stat.is_quoted == false \
			&& save.is_quoted == true)
			size += 2;
		else if (exp[i] == '\'' && stat.is_quoted == false \
			&& save.is_quoted == true)
			size += 2;
		save = stat;
		i++;
	}
	return (size);
}

int	is_quote_protected(char *c)
{
	static t_esc	stat = {false, false, false};
	static t_esc	save;
	int				is;

	check_quote(&stat, c);
	if (*c == '\'' && stat.is_quoted == true)
		is = 1;
	else if (*c == '"' && stat.is_quoted == true)
		is = 2;
	else if (*c == '"' && stat.is_quoted == false && save.is_quoted == true)
		is = 2;
	else if (*c == '\'' && stat.is_quoted == false && save.is_quoted == true)
		is = 1;
	else
		is = 0;
	save = stat;
	return (is);
}

char	*strcpy_quotes(char *dest, char *src, int size)
{
	size_t	i;
	int		is;

	i = 0;
	while (src[i])
	{
		is = is_quote_protected(&src[i]);
		if (is == 1)
		{
			dest[ft_strlen(dest)] = '"';
			dest[ft_strlen(dest)] = '\'';
			dest[ft_strlen(dest)] = '"';
		}
		else if (is == 2)
		{
			dest[ft_strlen(dest)] = '\'';
			dest[ft_strlen(dest)] = '"';
			dest[ft_strlen(dest)] = '\'';
		}
		else if (is == 0)
			dest[ft_strlen(dest)] = src[i];
		i++;
	}
	dest[size] = '\0';
	return (dest);
}

char	*protect_quotes(char *exp)
{
	int		size;
	char	*new;

	size = protect_new_size(exp) + ft_strlen(exp);
	new = ft_calloc(sizeof(char), size + 1);
	if (!new)
		return (NULL);
	new = strcpy_quotes(new, exp, size);
	free(exp);
	return (new);
}

char	*expand(char *str, t_list **env, int size)
{
	char	*exp;
	char	*new;

	//printf("\n%s\n", str);
	new = ft_substr(str, 1, size - 1);
	//printf("\n[expand] char* used to browse env: %s\n", new);
	if (!ft_strncmp(new, "?", 1))
		exp = ft_itoa(g_status);
	else
		exp = ft_strdup(env_find_key(new, env));
	//	printf("%s\n", exp[i]);
	free(new);
	//printf("%s\n", final);
	//free_array_2d(exp);
	if (exp)
		exp = protect_quotes(exp);
	return (exp);
}
