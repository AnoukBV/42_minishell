/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:29:34 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/29 15:44:05 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_print_member(void *mb)
{
	t_member	*m;

	m = (t_member *)mb;
  	if (!m)
		return ;
	if (!m->key)
		return ;
	ft_printf("%s=%s\n", m->key, m->value);
}
/*
static void	ft_env_p(t_hashtable **e)
{
	size_t		i;
	t_hashtable	*env;

	i = 0;
	env = *e;
	while (i < env->size)
	{
		env_print_member(env->member[i]);
		i++;
	}
}
*/
int	print_env(t_list **env, int key)
{
	int	exit;

	exit = 0;
	if (!(*env))
		return (1) ;
	if (key == EXPORT)
		exit = ft_exp_p(env);
	else
	{
	//	env_print_member((*env)->content);
		printf("\n[print_env] (*env): %p\n", *env);
		ft_lstiter(*env, &env_print_member);
	}
	return (exit);
}
