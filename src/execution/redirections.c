/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:08:41 by abernade          #+#    #+#             */
/*   Updated: 2024/06/05 12:45:16 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	do_redir_list(t_redir_list **r_list, t_pipeline *pipeline)
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
		{
			open_error(node->target_filename, pipeline);
			return (1);
		}
		else if (dup2(fd, node->fd_to_redirect) == -1)
		{
			dup2_error();
			close(fd);
		}
		free(node->target_filename);
		free(node);
		node = next;
	}
	*r_list = NULL;
	return (0);
}

int	do_redirections(t_command *cmd, t_pipeline *pipeline)
{
	if (cmd->prev)
	{
		if (dup2(cmd->pipe_left[0], 0) == -1)
			dup2_error();
		close(cmd->pipe_left[0]);
		remove_fd(cmd->pipe_left[0], &pipeline->fd_list);
	}
	if (cmd->next)
	{
		if (dup2(cmd->pipe_right[1], 1) == -1)
			dup2_error();
		close(cmd->pipe_right[1]);
		remove_fd(cmd->pipe_right[1], &pipeline->fd_list);
	}
	return (do_redir_list(&cmd->redir_list, pipeline));
}

void	set_pipes(t_pipeline *pipeline, t_command *cmd)
{
	int	pfd[2];
	
	if (cmd->prev)
	{
		cmd->pipe_left[0] = cmd->prev->pipe_right[0];
		cmd->pipe_left[1] = cmd->prev->pipe_right[1];
	}
	if (cmd->next)
	{
		if (pipe(pfd) == -1)
			generic_error(pipeline);
		cmd->pipe_right[0] = pfd[0];
		cmd->pipe_right[1] = pfd[1];
	}
}
