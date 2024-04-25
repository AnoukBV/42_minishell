/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:46:39 by abernade          #+#    #+#             */
/*   Updated: 2024/04/25 16:10:24 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
*	Close all file descriptors in the list
*	Free all nodes of the list and set it to NULL
*/
void	close_fd_list(t_fd_list **fds)
{
	t_fd_list	*node;
	t_fd_list	*next;
	
	node = *fds;
	while (node)
	{
		next = node->next;
		close(node->fd);
		free(node);
		node = next;
	}
	*fds = NULL;
}

int	remove_fd(int fd, t_fd_list **fds)
{
	t_fd_list	*node;
	t_fd_list	*prev;

	if (fds == NULL || *fds == NULL)
		return ;
	node = *fds;
	prev = NULL;
	while (node != NULL && node->fd != fd)
	{
		prev = node;
		node = node->next;
	}
	if (node == NULL)
		return (-1);
	if (prev == NULL)
		*fds = node->next;
	else
		prev->next = node->next;
	free(node);
	return (0);
}

void	add_fd(int fd, t_fd_list **fds)
{
	t_fd_list	*node;
	t_fd_list	*new_node;

	node = *fds;
	new_node = malloc(sizeof(t_fd_list));
	if (!new_node)
		malloc_error();
	new_node->fd = fd;
	new_node->next = NULL;
	if (!node)
		*fds = new_node;
	else
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
}
