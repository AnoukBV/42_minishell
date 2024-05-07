/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:40:57 by abernade          #+#    #+#             */
/*   Updated: 2024/04/29 15:19:58 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	destroy_redir_list(t_redir_list **redir_list)
{
	t_redir_list	*node;
	t_redir_list	*next;

	node = *redir_list;
	while (node)
	{
		next = node->next;
		free(node->target_filename);
		free(node);
		node = next;
	}
	*redir_list = NULL;
}

void	destroy_cmd_list(t_command *cmd)
{
	t_command	*tmp;
	int			i;
	
	while (cmd)
	{
		free(cmd->command);
		if (cmd->argv)
		{
			i = 0;
			while (cmd->argv[i])
			{
				free(cmd->argv[i]);
				i++;
			}
			free(cmd->argv);
		}
		destroy_redir_list(&cmd->redir_list);
		tmp = cmd->next;
		free(cmd);
		cmd = tmp;
	}
}

void	destroy_pipeline(t_pipeline *pipeline)
{
	close_fd_list(&pipeline->fd_list);
	destroy_cmd_list(pipeline->cmd_list);
	free(pipeline);
}

void	prepare_pipeline(t_pipeline *pipeline)
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

/*
*	/!\ Currently unused /!\
*/
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
