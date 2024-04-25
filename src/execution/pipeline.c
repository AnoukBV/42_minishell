/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:40:57 by abernade          #+#    #+#             */
/*   Updated: 2024/04/25 17:05:41 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	prepare_pipeline(t_pipeline *pipeline)
{
	t_command	*cmd;
	int			pfd[2];

	cmd = pipeline->cmd_list;
	while (cmd->next)
	{
		if (pipe(pfd) == -1)
			pipe_error(pipeline);
		cmd->pipe_right[0] = pfd[0];
		cmd->pipe_right[1] = pfd[1];
		cmd = cmd->next;
		cmd->pipe_left[0] = pfd[0];
		cmd->pipe_left[1] = pfd[1];
		add_fd(pfd[0], &pipeline->fd_list);
		add_fd(pfd[1], &pipeline->fd_list);
	}
}

t_pipeline	*init_pipeline(t_command *cmd_lst, char **envp)
{
	t_pipeline	*pipeline;

	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		malloc_error();
	pipeline->cmd_list = cmd_lst;
	pipeline->envp = envp;
	pipeline->fd_list = NULL;
	prepare_pipeline(pipeline);
	return (pipeline);
}
