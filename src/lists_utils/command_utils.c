/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:12:51 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/26 07:47:04 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_cmd_one(t_command *cmd, t_bool rm_heredoc)
{
	if (cmd->command)
		free(cmd->command);
	if (cmd->argv && cmd->is_argv == true)
		free_array_2d((char **)cmd->argv);
	if (cmd->redir_list)
		destroy_redir_list(&cmd->redir_list, rm_heredoc);
	if (cmd)
		free(cmd);
}

void	destroy_cmd_list(t_command **cmd, t_bool rm_heredoc)
{
	t_command	*tmp;

	while (*cmd)
	{
		tmp = (*cmd)->next;
		destroy_cmd_one(*cmd, rm_heredoc);
		*cmd = tmp;
	}
}

t_command	*command_last(t_command *command)
{
	while (command)
	{
		if (!command->next)
			return (command);
		command = command->next;
	}
	return (command);
}

void	command_addback(t_command **list, t_command *new)
{
	t_command	*tmp;

	if (*list == NULL && new)
		*list = new;
	else if (new && list)
	{
		tmp = command_last(*list);
		tmp->next = new;
	}
}
