/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:23:11 by aboulore          #+#    #+#             */
/*   Updated: 2024/04/30 19:37:42 by aboulore         ###   ########.fr       */
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
	return (false);
}

t_btree	*malloc_bst(void)
{
	t_btree	*node;
	t_pcmd	*cmd;

	cmd = init_cmd();
	node = btree_create_node(cmd);
	return (node);
}

t_pcmd	*init_cmd(void)
{
	t_pcmd	*cmd;

	cmd = malloc(sizeof(t_pcmd));
	if (!cmd)
		return (NULL);
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->cmd = NULL;
	cmd->redir_list = NULL;
	return (cmd);
}
