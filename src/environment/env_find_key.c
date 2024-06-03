/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:59:25 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/03 14:40:17 by aboulore         ###   ########.fr       */
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