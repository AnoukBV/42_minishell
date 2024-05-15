/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:59:25 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/15 11:30:18 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

char	*env_find_key(t_member **member, char *key, int size)
{
	int	i;

	i = 0;
	while (i < size && member[i])
	{
		if (member[i]->key && !ft_strncmp(member[i]->key, key, ft_strlen(key)))
			return (member[i]->value);
		i++;
	}
	return ("\0");
}

t_member	*env_find_tmemb(t_member **member, char *key, int size)
{
	int	i;

	i = 0;
	(void)size;
	while (member[i])
	{
		if (member[i]->key && !ft_strncmp(member[i]->key, key, ft_strlen(key)))
			return (member[i]);
		i++;
	}
	return (NULL);
}

/*
void	export_expansion(char *str, t_hashtable *env)
{
	char	*save;

	if (ft_strchr(str, '$'))
	{
	  	save = str;
		if (ft_strlen(str) == 2 && str[1] == '?')
			str = ft_itoa(g_status);
		else
			inspect_token(&save, &env);
		free(save);
	}
}*/
