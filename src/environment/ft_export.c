/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:19:12 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/09 00:39:22 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static void	export_print(t_hashtable *env)

void	ft_export(t_hashtable *env, char *str)
{
	if (str == NULL)
		export_print(env);
	else
		return ;
}*/

char	*env_find_key(t_member **member, char *key, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (member[i]->key && !ft_strncmp(member[i]->key, key, ft_strlen(key)))
			return (member[i]->value);
		i++;
	}
	return (NULL);
}
