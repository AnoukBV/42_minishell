/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 23:50:46 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/09 15:32:49 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**transform_envp(t_hashtable *env)
{
	char	**final;
	char	*tmp;
	size_t	i;

	i = 1;
	if (!env)
		return (NULL);
	final = ft_calloc(sizeof(char *), env->size + 1);
	if (!final)
		return (NULL);
	final[0] = ft_itoa(env->size);
	while (i < env->size + 1)
	{
	  	if (env->member[i - 1])
		{
	  		tmp = ft_strjoin(env->member[i - 1]->key, "=");
			final[i] = ft_strjoin(tmp, env->member[i - 1]->value);
			free(tmp);
			tmp = NULL;
		}
		else
			final[i] = NULL;
		i++;
	}
	return (final);
}
