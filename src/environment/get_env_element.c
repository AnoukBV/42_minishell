/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:10:13 by abernade          #+#    #+#             */
/*   Updated: 2024/05/16 14:28:38 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
/*
t_member	*get_env_element(t_hashtable *env, char *key)
{
	int	i;

	i = 0;
	while (i < (int)env->size)
	{
		if (ft_strncmp(env->member[i]->key, key, ft_strlen(key) + 1) == 0)
			return (env->member[i]);
		i++;
	}
	return (NULL);
}
*/
char	**get_path_list(t_list	*env)
{
	char		**p_list;
	t_member	*env_path;
	
	env_path = env_find_tmemb("PATH", &env);
	p_list = ft_split(env_path->value, ':');
	return (p_list);
}
