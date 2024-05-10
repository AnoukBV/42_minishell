/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:10:13 by abernade          #+#    #+#             */
/*   Updated: 2024/05/09 16:34:37 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_member	*get_env_element(t_hashtable *env, char *key)
{
	int	i;

	i = 0;
	while (i < env->size)
	{
		if (ft_strncmp(env->member[i]->key, key) == 0)
			return (env->member[i])
		i++;
	}
	return (NULL);
}

char	**get_path_list(t_hashtable	*env)
{
	char		**p_list;
	t_member	*env_path;
	
	env_path = get_env_element(env, "PATH");
	p_split = ft_split(env_path->value, ':');
}
