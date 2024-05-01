/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:33:27 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/01 08:55:07 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delmemb_env(t_member *member)
{
	if (!member)
	{
		free(member);
		return ;
	}
	free(member->key);	
	free(member->value);	
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
	free(env->member);
	free(env);
}

/*
 *
 * SUREMENT UN PEU TROP DE FREE(ENV->MEMBER) : POSSIBILITE DE DOUBLE FREE
 *
 */
