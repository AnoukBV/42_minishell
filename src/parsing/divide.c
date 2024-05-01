/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:41:22 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/01 10:27:07 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	until_next(t_list **inputs, int next)
{
	size_t		size;
	t_wd_desc	*tok;
	t_list		*tmp;

	tmp = *inputs;
	size = 0;
	tok = (t_wd_desc *)tmp->content;
	if (tok->flags == next)
		return (1);
	while (tmp && tok->flags != next && tok->flags != T_PIPE)
	{
		size++;
		tmp = tmp->next;
		if (tmp)
			tok = (t_wd_desc *)tmp->content;
	}
	if (size == 0 && tmp == NULL)
		size = ft_lstsize(*inputs);
	return (size);
}

static void	isolate_cmd(t_command **cmd, t_list **inputs, size_t size)
{
	t_wd_desc	*tok;
	t_wd_desc	*new;

	(void)size;
	tok = (t_wd_desc *)(*inputs)->content;
	new = new_wd_desc(tok->flags, ft_strdup(tok->word));
	if (new->word != NULL)
		ft_lstadd_back(&(*cmd)->cmd, ft_lstnew(new));
}

static void	isolate_redir(t_command **cmd, t_list **inputs)
{
	t_redir_list	*new;
	t_wd_desc		*tok;
	t_list			*tmp;

	tok = (t_wd_desc *)(*inputs)->content;
	new = malloc(sizeof(t_redir_list));
	if (!new)
		return ;
	new->type = tok->flags;
	tok = (t_wd_desc *)(*inputs)->next->content;
	tmp = *inputs;
	new->target_filename = ft_strdup(tok->word);
	new->next = NULL;
	addback_redir(&(*cmd)->redir_list, new);
	if ((*inputs)->next)
		(*inputs) = (*inputs)->next;
}

static void	create_tree(t_list **inputs, \
	t_btree **holder, size_t size)
{
	t_btree			*node;
	t_list			*tmp;
	t_wd_desc		*tok;
	t_command		*cmd;

	node = malloc_bst();
	tok = (t_wd_desc *)(*inputs)->content;
	tmp = *inputs;
	cmd = (t_command *)node->item;
	if (tok->flags == T_PIPE)
		cmd->flags = T_PIPE;
	else
		cmd->flags = T_WORD;
	while (size > 0 && cmd->flags != T_PIPE && tmp)
	{
		if (is_redir(tmp) == true)
			isolate_redir(&cmd, &tmp);
		else
			isolate_cmd(&cmd, &tmp, size);
		size--;
		tmp = tmp->next;
	}
	*holder = node;
}

void	divide(t_list **inputs, t_btree **tree)
{
	t_btree		*holder;
	size_t		size;

	holder = NULL;
	size = 0;
	while (*inputs)
	{
		size = until_next(inputs, T_PIPE);
		create_tree(inputs, &holder, size);
		if (!(*tree))
			(*tree) = holder;
		else if (((t_wd_desc *)(*inputs)->content)->flags == T_PIPE)
		{
			holder->left = (*tree);
			(*tree) = holder;
		}
		else
			(*tree)->right = holder;
		while (size > 0)
		{
			(*inputs) = (*inputs)->next;
			size--;
		}
		holder = NULL;
	}
}
