/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:30:31 by abernade          #+#    #+#             */
/*   Updated: 2024/05/09 18:39:29 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern int	g_status;

/*
*	Returns -1 on open() error, 0 otherwise
*/
static void	do_redir_list(t_redir_list **r_list)
{
	int				fd;
	t_redir_list	*node;
	t_redir_list	*next;

	node = *r_list;
	while (node != NULL)
	{
		next = node->next;
		fd = open(node->target_filename, node->open_flags, 0644);
		if (fd == -1)
			open_error(node->target_filename);
		if (dup2(fd, node->fd_to_redirect) == -1)
			dup2_error();
		close(fd);
		free(node->target_filename);
		free(node);
		node = next;
	}
	*r_list = NULL;
}

/*
*	Returns -1 on open() error, 0 otherwise
*/
static void	do_redirections(t_command *cmd, t_fd_list **fd_list)
{
	if (cmd->prev) // left pipe
	{
		if (dup2(cmd->pipe_left[0], 0) == -1)
			dup2_error();
		remove_fd(cmd->pipe_left[0], fd_list);
	}
	if (cmd->next) // right pipe
	{
		if (dup2(cmd->pipe_right[1], 1) == -1)
			dup2_error();
		remove_fd(cmd->pipe_right[1], fd_list);
	}
	do_redir_list(&cmd->redir_list);
}

static void	child_exec(t_pipeline *pipeline, t_command *cmd)
{
	do_redirections(cmd, &pipeline->fd_list);
	close_fd_list(&pipeline->fd_list);
	if (execve(cmd->command, cmd->argv, pipeline->envp) == -1)
	{
		//destroy_pipeline(pipeline);
		//free_env(*pipeline->cmd_list->env);		
		execve_error(cmd->command);
	}
}

static void	end_pipeline(t_pipeline *pipeline)
{
	close_fd_list(&pipeline->fd_list);
	wait_all_pid(&pipeline->pid_list);
}

void	execute_pipeline(t_pipeline *pipeline)
{
	int			pid;
	t_command	*cmd;


	cmd = pipeline->cmd_list;
	//prepare_pipeline(pipeline);
	while (cmd)
	{
		pid = fork();
		if (pid == -1)
			fork_error(pipeline);
		else if (pid == 0)
		{
			child_exec(pipeline, cmd);
			break;
		}
		add_pid(pid, &pipeline->pid_list);
		if (cmd->next == NULL)
			end_pipeline(pipeline);
		cmd = cmd->next;
	}
	destroy_pipeline(pipeline);
}
