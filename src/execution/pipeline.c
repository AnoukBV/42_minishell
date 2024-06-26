/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:40:57 by abernade          #+#    #+#             */
/*   Updated: 2024/06/26 13:25:12 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_redir_list(t_redir_list **redir_list, t_bool rm_heredoc)
{
	t_redir_list	*node;
	t_redir_list	*next;

	node = *redir_list;
	while (node)
	{
		if (node->heredoc && rm_heredoc \
			&& !access(node->target_filename, F_OK))
		{
			if (unlink(node->target_filename))
				simple_generic_error("minishell: failed to unlink heredoc");
		}
		next = node->next;
		free(node->target_filename);
		free(node);
		node = next;
	}
	*redir_list = NULL;
}

void	ifree_array_2d(char **array)
{
	int	i;
	int	size;

	i = 0;
	size = ft_atoi(array[0]);
	while (i < size)
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void	destroy_pipeline(t_pipeline *pipeline, int x)
{
	close_fd_list(&pipeline->fd_list);
	destroy_pid_list(&pipeline->pid_list);
	destroy_cmd_list(&pipeline->cmd_list, true);
	if (x == EXIT)
	{
		clear_statics();
		free(pipeline);
	}
}

t_pipeline	*init_pipeline(t_command *cmd_lst, t_list *env)
{
	t_pipeline	*pipeline;

	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		malloc_error();
	pipeline->cmd_list = cmd_lst;
	pipeline->envp = env;
	pipeline->fd_list = NULL;
	pipeline->pid_list = NULL;
	return (pipeline);
}
