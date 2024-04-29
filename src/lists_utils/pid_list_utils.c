/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 00:46:48 by abernade          #+#    #+#             */
/*   Updated: 2024/04/29 02:57:55 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	wait_all_pid(t_pid_list **pid_list)
{
	t_pid_list	*node;
	t_pid_list	*next;
	t_pid_list	*prev;

	if (pid_list == NULL || *pid_list == NULL)
		return ;
	prev = NULL;
	node = *pid_list;
	while (node)
	{
		waitpid(node->pid, NULL, 0);
		if (prev == NULL)
			*pid_list = node->next;
		else
			prev->next = node->next;
		next = node->next;
		free(node);
		node = next;
	}
}

void	remove_pid(int pid, t_pid_list **pid_list)
{
	t_pid_list	*node;
	t_pid_list	*prev;

	if (pid_list == NULL || *pid_list == NULL)
		return ;
	node = *pid_list;
	prev = NULL;
	while (node != NULL && node->pid != pid)
	{
		prev = node;
		node = node->next;
	}
	if (prev == NULL)
		*pid_list = node->next;
	else
		prev->next = node->next;
	free(node);
}

void	add_pid(int pid, t_pid_list **pid_list)
{
	t_pid_list	*node;
	t_pid_list	*new_node;

	node = *pid_list;
	new_node = malloc(sizeof(t_pid_list));
	if (!new_node)
		malloc_error();
	new_node->pid = pid;
	new_node->next = NULL;
	if (!node)
		*pid_list = new_node;
	else
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
}
