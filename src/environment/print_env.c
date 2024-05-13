/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:29:34 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/13 12:25:22 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *
 * pour les builtins export sans arg et env sans arg
 *	ATTENTION A SECURIT QUAND ON ARRIV AU MAX DE CLEFS
 */

static void	ft_env_p(t_hashtable **e)
{
	size_t		i;
	t_hashtable	*env;

	i = 0;
	env = *e;
	while (i < env->size)
	{
	  	if (!env->member[i])
			break ;
		ft_putstr_fd(env->member[i]->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(env->member[i]->value, 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

void	print_env(t_hashtable **env, int key)
{
	if (!(*env))
		return ;
	if (key == EXPORT)
		ft_exp_p(env);
	else
		ft_env_p(env);
}
