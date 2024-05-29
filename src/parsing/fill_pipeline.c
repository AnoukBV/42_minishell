/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:54:49 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/29 13:36:12 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	delete_operator(t_command **head, t_command *del)
{
	if (*head == NULL || del == NULL)
		return ;
	if (*head == del)
		*head = del->next;
	printf("[delete_operator] del: %p\n", del);
	printf("[delete_operator] del->next->prev: %p\n", del->next->prev);
	printf("[delete_operator] del->prev: %p\n", del->prev);
	printf("[delete_operator] del->next: %p\n", del->next);
	//if (del->next != NULL)
	//	del->next->prev = del->prev;
	//if (del->prev != NULL)
	//	del->prev->next = del->next;
}
*/
void	add_flags(t_command **cmd)
{
	t_command	*tmp;
	t_command	*save;

	tmp = *cmd;
	if (!tmp)
		return ;
	//printf("[add_flags] tmp: %p, tmp->flags: %i\n", tmp, tmp->flags);
	save = tmp;
	while (tmp)
	{
		if (tmp->flags != T_WORD && tmp->flags != EMPTY)
		{
			save->flags = tmp->flags;
			save->next = tmp->next;
			save->next->prev = save;
			//tmp->next->prev = tmp->prev;
			//delete_operator(cmd, tmp);
			destroy_cmd_one(tmp);
			tmp = save;
		}
	  	save = tmp;
		tmp = tmp->next;
		//if (tmp)
		//	tmp->prev = save;
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
	order_commands(&cmd_list, tree);
	add_flags(&cmd_list);
	*pipeline = init_pipeline(cmd_list, env);
}
