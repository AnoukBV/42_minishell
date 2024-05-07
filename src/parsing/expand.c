/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:00:48 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/07 14:27:19 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*seek_env(char *key, t_hashtable **env)
{
	t_member	**table;
	size_t		i;

	i = 0;
	table = (t_member **)(*env)->member;
	while (i < (*env)->size - 1)
	{
		if (table[i] && table[i]->key && \
			!ft_strncmp(table[i]->key, key, ft_strlen(key)))
			return (table[i]->value);
		i++;
	}
	return ("\0");
}

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

char	*expand(char *str, t_hashtable **env, size_t size)
{
	char	**exp;
	char	**to_exp;
	char	*final;
	char	*new;
	size_t	i;

	i = 0;
	final = NULL;
	new = ft_substr(str, 0, size - 1);
	if (str[0] == '\"')
		delete_quotes(&new);
	to_exp = ft_split(new, '$');
	free(new);
	exp = ft_calloc(sizeof(char *), ft_arrlen(to_exp) + 1);
	if (!exp)
		return (NULL);
	while (to_exp[i])
	{
		exp[i] = ft_strdup(seek_env(to_exp[i], env));
		i++;
	}
	free_array_2d(to_exp);
	final = ft_superjoin(exp, NULL);
	free_array_2d(exp);
	return (final);
}
