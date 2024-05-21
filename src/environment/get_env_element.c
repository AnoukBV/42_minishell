/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:10:13 by abernade          #+#    #+#             */
/*   Updated: 2024/05/21 15:35:46 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	p_list = ft_split(env_path->value, ':');
	return (p_list);
}
