/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:33:27 by aboulore          #+#    #+#             */
/*   Updated: 2024/04/26 12:19:02 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delmemb_env(t_member *member)
{
	if (!member)
		return ;
	
	free(member);
}

void	free_env(t_hashtable *env)
{
	size_t	i;

	i = 0;
	if (!env)
		return ;
	while (i < env->size)
	{
		delmemb_env(env->member[i]);
		i++;
	}
	free(*env);
}
