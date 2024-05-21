/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:08:41 by abernade          #+#    #+#             */
/*   Updated: 2024/05/21 12:36:10 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
*	Returns -1 on open() error, 0 otherwise
*/
static void	do_redir_list(t_redir_list **r_list, t_pipeline *pipeline)
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
			open_error(node->target_filename, pipeline);
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
void	do_redirections(t_command *cmd, t_pipeline *pipeline)
{
	if (cmd->prev) // left pipe
	{
		if (dup2(cmd->pipe_left[0], 0) == -1)
			dup2_error();
		remove_fd(cmd->pipe_left[0], &pipeline->fd_list);
	}
	if (cmd->next) // right pipe
	{
		if (dup2(cmd->pipe_right[1], 1) == -1)
			dup2_error();
		remove_fd(cmd->pipe_right[1], &pipeline->fd_list);
	}
	do_redir_list(&cmd->redir_list, pipeline);
}
