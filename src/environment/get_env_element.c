/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:10:13 by abernade          #+#    #+#             */
/*   Updated: 2024/06/26 07:45:27 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_member	*get_env_element(t_list *env, char *key)
{
	t_member	*env_elem;

	while (env)
	{
		env_elem = env->content;
		if (ft_strncmp(env_elem->key, key, ft_strlen(key) + 1) == 0)
			return (env_elem);
		env = env->next;
	}
	return (NULL);
}

char	**get_path_list(t_list	*env)
{
	char		**p_list;
	t_member	*env_path;

	env_path = env_find_tmemb("PATH", &env);
	if (!env_path)
		return (NULL);
	p_list = ft_split(env_path->value, ':');
	return (p_list);
}
