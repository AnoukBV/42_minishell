/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:00:48 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/28 16:43:37 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static void	delete_quotes(char **new)
{
	char	**tmp;
	char	*str;

	tmp = ft_split(*new, '\"');
	free(*new);
	*new = NULL;
	str = ft_strdup(tmp[0]);
	free_array_2d(tmp);
	tmp = NULL;
	*new = str;
}
*/
char	*ft_superjoin(char **strs, char *sep)
{
	size_t	size;
	size_t	i;
	char	*str;

	size = ft_arrlen(strs);
	i = 0;
	if (sep)
		str = ft_calloc(sizeof(char), (ft_megalen(strs) + \
			ft_strlen(sep) * size + 1));
	else
		str = ft_calloc(sizeof(char), ft_megalen(strs) + 1);
	if (!str)
		return (NULL);
	while (i < size)
	{
		ft_strlcat(str, (const char *)strs[i], ft_strlen(str) \
			+ ft_strlen(strs[i]) + 1);
		if (sep)
			ft_strlcat(str, (const char *)strs[i], ft_strlen(str) \
				+ ft_strlen(sep) + 1);
		i++;
	}
	if (size == 0)
		return (NULL);
	printf("%s\n", str);
	return (str);
}

char	*expand(char *str, t_list **env, int size)
{
	char	*exp;
	char	*new;

	new = ft_substr(str, 1, size - 1);
	printf("\nIn expand, char* used to browse env: %s\n", new);
	exp = ft_strdup(env_find_key(new, env));
	//	printf("%s\n", exp[i]);
	free(new);
	//printf("%s\n", final);
	//free_array_2d(exp);
	return (exp);
}
