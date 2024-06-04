/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:54:49 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/04 15:04:08 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_flags(t_command **cmd)
{
	t_command	*tmp;
	t_command	*save;

	tmp = *cmd;
	if (!tmp)
		return ;
	save = tmp;
	while (tmp)
	{
		if (tmp->flags != T_WORD && tmp->flags != EMPTY)
		{
			save->flags = tmp->flags;
			save->next = tmp->next;
			save->next->prev = save;
			destroy_cmd_one(tmp);
			tmp = save;
		}
		save = tmp;
		tmp = tmp->next;
	}
}

void	order_commands(t_command **cmd, t_btree *tree)
{
	if (!tree)
		return ;
	if (tree->left)
		order_commands(cmd, tree->left);
	command_addback(cmd, (t_command *)tree->item);
	if (tree->right)
		order_commands(cmd, tree->right);
}

void	fill_pipeline(t_pipeline **pipeline, t_btree *tree, t_list *env)
{
	t_command	*cmd_list;

	cmd_list = NULL;
	if (tree)
		order_commands(&cmd_list, tree);
	if (cmd_list)
		add_flags(&cmd_list);
	*pipeline = init_pipeline(cmd_list, env);
}
