/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:23:11 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/15 17:38:57 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	addback_redir(t_redir_list **redir, t_redir_list *new)
{
	t_redir_list	*tmp;

	tmp = *redir;
	if (!tmp && new)
	{
		(*redir) = new;
		return ;
	}
	while (tmp)
	{
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	tmp->next = new;
}

t_bool	is_redir(t_list *inputs)
{
	t_wd_desc	*tok;

	tok = (t_wd_desc *)inputs->content;
	if (tok->flags == T_RED_OUT || tok->flags == T_APP_OUT \
		|| tok->flags == T_RED_IN || tok->flags == T_APP_IN)
		return (true);
	else if (tok->flags % 1000 == T_RED_OUT || tok->flags % 1000 == T_APP_OUT \
		|| tok->flags % 1000 == T_RED_IN || tok->flags % 1000 == T_APP_IN)
		return (true);
	return (false);
}

t_btree	*init_bst(t_hashtable **env)
{
	t_btree		*node;
	t_command	*cmd;

	cmd = init_cmd(env);
	node = btree_create_node(cmd);
	return (node);
}

t_command	*init_cmd(t_hashtable **env)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->env = env;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->argv = NULL;
	cmd->is_argv = true;
	cmd->command = NULL;
	cmd->redir_list = NULL;
	return (cmd);
}

void	new_branch(t_wd_desc *tok, t_btree *holder, t_btree **tree)
{
	if (!(*tree))
		(*tree) = holder;
	else if (tok->flags == T_PIPE || tok->flags == T_OR || \
		tok->flags == T_AND)
	{
		holder->left = (*tree);
		(*tree) = holder;
	}
	else
		(*tree)->right = holder;
}
