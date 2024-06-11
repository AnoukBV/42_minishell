/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:58:43 by abernade          #+#    #+#             */
/*   Updated: 2024/06/11 14:43:52 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_status;

void	clear_statics(void)
{
	get_prompt(true);
}

int	main(int ac, char **av, char **envp)
{
	t_list	*env;

	(void)av;
	(void)ac;
	g_status = 0;
	env = NULL;
	set_hashtable(envp, &env);
	shell_prompt(&env);
	ft_lstclear(&env, &del_member);
	ft_putstr_fd("exit\n", 1);
	clear_statics();
	return (0);
}
