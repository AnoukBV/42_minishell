/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:29:34 by aboulore          #+#    #+#             */
/*   Updated: 2024/04/26 10:43:47 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *
 * pour les builtins export sans arg et env sans arg
 *
 */

//static void	ft_export_p(t_hashtable *env)

static void	ft_env_p(t_hashtable *env)
{
	size_t	i;

	i = 0;
	while (i < env->size && env->member[i])
	{
		ft_putstr_fd(env->member[i]->key, 1);
		ft_putstr_fd("=");
		ft_putstr_fd(env->member[i]->value, 1);
		ft_putstr_fd("\n");
		i++;
	}
}

void	print_env(t_hashtable *env, int key)
{
	if (!env)
		return ;
	if (key == EXPORT)
		ft_export_p(env);
	else
		ft_env_p(env);
}
