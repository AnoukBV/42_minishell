/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:30:31 by abernade          #+#    #+#             */
/*   Updated: 2024/04/29 14:55:37 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern int	g_status;

/*
*	Returns -1 on open() error, 0 otherwise
*/
static int	do_redir_list(t_redir_list **r_list)
{
	int				fd;
	t_redir_list	*node;
	t_redir_list	*next;

	node = *r_list;
	while (node != NULL)
	{
		next = node->next;
		fd = open(node->target_filename, node->open_flags, 0666);
		if (fd == -1)
			return (-1);
		if(dup2(fd, node->fd_to_redirect) == -1)
			dup2_error();
		free(node->target_filename);
		free(node);
		node = next;
	}
	*r_list = NULL;
	return(0);
}

/*
*	Returns -1 on open() error, 0 otherwise
*/
static int	do_redirections(t_command *cmd, t_fd_list **fd_list)
{
	if (cmd->prev) // left pipe
	{
		if(dup2(cmd->pipe_left[0], 0) == -1)
			dup2_error();
		remove_fd(cmd->pipe_left[0], fd_list);
	}
	if (cmd->next) // right pipe
	{
		if(dup2(cmd->pipe_right[1], 1) == -1)
			dup2_error();
		remove_fd(cmd->pipe_right[1], fd_list);
	}
	return (do_redir_list(&cmd->redir_list));
}

static void	child_exec(t_pipeline *pipeline, t_command *cmd)
{
	if (do_redirections(cmd, &pipeline->fd_list) == -1)
		open_error(pipeline);
	close_fd_list(&pipeline->fd_list);
	if (execve(cmd->command, cmd->argv, pipeline->envp) == -1)
		execve_error();
}

void	execute_pipeline(t_pipeline *pipeline)
{
	int			pid;
	t_command	*cmd;

	cmd = pipeline->cmd_list;
	prepare_pipeline(pipeline);
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
		if (cmd->next == NULL)
		{
			close_fd_list(&pipeline->fd_list);
			waitpid(pid, &g_status, 0);
			wait_all_pid(&pipeline->pid_list);
		}
		else
			add_pid(pid, &pipeline->pid_list);
		cmd = cmd->next;
	}
}
