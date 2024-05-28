/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:59:25 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/28 10:42:10 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

char	*env_find_key(char *key, t_list	**env)
{
	t_list		*tmp;
	t_member	*m;

	tmp = *env;
	if (!tmp)
		return ("\0");
	while (tmp)
	{
		m = (t_member *)tmp->content;
		if (m->key && !ft_strncmp(m->key, key, ft_strlen(key) + 1))
			return (m->value);
		tmp = tmp->next;
	}
	return (0);
}

t_member	*env_find_tmemb(char *key, t_list **env)
{
	t_list		*tmp;
	t_member	*m;

	tmp = *env;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		m = (t_member *)tmp->content;
		if (m->key && !ft_strncmp(m->key, key, ft_strlen(key) + 1))
			return (m);
		tmp = tmp->next;
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
