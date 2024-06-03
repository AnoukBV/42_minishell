/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:29:34 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/03 14:36:26 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_print_member(void *mb)
{
	t_member	*m;

	m = (t_member *)mb;
  	if (!m)
		return ;
	if (!m->key || !m->value)
		return ;
	ft_printf("%s=%s\n", m->key, m->value);
}

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
		//printf("\n[print_env] (*env): %p\n", *env);
		ft_lstiter(*env, &env_print_member);
	}
	return (exit);
}
