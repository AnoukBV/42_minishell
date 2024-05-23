/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:29:34 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/16 14:11:42 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *
 * pour les builtins export sans arg et env sans arg
 *	ATTENTION A SECURIT QUAND ON ARRIV AU MAX DE CLEFS
 */
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
	if (!(*env))
		return (1) ;
	if (key == EXPORT)
		ft_exp_p(env);
	else
		ft_lstiter(*env, &env_print_member);
	return (0);
}
