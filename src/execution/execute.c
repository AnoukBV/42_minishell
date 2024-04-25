/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:30:31 by abernade          #+#    #+#             */
/*   Updated: 2024/04/25 17:06:12 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_pipeline(t_command *cmd_lst, char **envp)
{
	int			pid;
	t_pipeline	*pipeline;

	pipeline = init_pipeline(cmd_lst, envp);
	if (is_builtin(cmd_lst->command) && cmd_lst->next == NULL)
	{
		/*
		*	todo
		*/
	}
}
