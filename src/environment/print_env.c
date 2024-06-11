/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:29:34 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/11 14:46:52 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_print_member(void *mb)
{
	t_member	*m;

	m = (t_member *)mb;
	if (!ft_strncmp(ENV_KEY_EXIT_CODE, m->key, ft_strlen(ENV_KEY_EXIT_CODE)))
		return ;
	if (!m)
		return ;
	if (!m->key || !m->value)
		return ;
	ft_printf("%s=%s\n", m->key, m->value);
}

int	print_env(t_list **env, char **args, int key)
{
	int	exit;

	exit = 0;
	if (!(*env))
		return (1);
	if (key == EXPORT)
		exit = ft_exp_p(env);
	else
	{
		if (ft_arrlen(args) > 1)
		{
			ft_putstr_fd("minishell: env: invalid number of arguments\n", 2);
			return (1);
		}
		ft_lstiter(*env, &env_print_member);
	}
	return (exit);
}
