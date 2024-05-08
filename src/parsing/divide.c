/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:41:22 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/08 17:14:19 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	until_next_op(t_list **inputs)
{
	size_t		size;
	t_wd_desc	*tok;
	t_list		*tmp;

	tmp = *inputs;
	size = 0;
	tok = (t_wd_desc *)tmp->content;
	if (tok->flags == T_PIPE || tok->flags == T_OR || tok->flags == T_AND)
		return (1);
	while (tmp && (tok->flags != T_PIPE && tok->flags != T_OR && tok->flags != T_AND))
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
		ft_lstadd_back((t_list **)&(*cmd)->argv, ft_lstnew(new));
	(*cmd)->next = NULL;
}

static void	isolate_redir(t_command **cmd, t_list **inputs)
{
	t_redir_list	*new;
	t_wd_desc		*tok;
	//t_list			*tmp;

	tok = (t_wd_desc *)(*inputs)->content;
	new = malloc(sizeof(t_redir_list));
	if (!new)
		return ;
	assignate_flags_dir(tok->flags, &new->open_flags, &new->fd_to_redirect);
	//new->type = tok->flags;
	tok = (t_wd_desc *)(*inputs)->next->content;
	//tmp = *inputs;
	new->target_filename = ft_strdup(tok->word);
	new->next = NULL;
	addback_redir(&(*cmd)->redir_list, new);
	if ((*inputs)->next)
		(*inputs) = (*inputs)->next;
	(*cmd)->next = NULL;
}

static void	create_tree(t_list **inputs, \
	t_btree **holder, size_t size, t_hashtable **env)
{
	t_btree			*node;
	t_list			*tmp;
	t_wd_desc		*tok;
	t_command		*cmd;

	node = init_bst(env);
	tok = (t_wd_desc *)(*inputs)->content;
	tmp = *inputs;
	cmd = (t_command *)node->item;
	if (tok->flags == T_PIPE || tok->flags == T_OR || tok->flags == T_AND)
		cmd->flags = tok->flags;
	else
		cmd->flags = T_WORD;
	while (size > 0 && cmd->flags == T_WORD && tmp)
	{
		if (is_redir(tmp) == true)
		{
			isolate_redir(&cmd, &tmp);
			size--;
		}
		else
			isolate_cmd(&cmd, &tmp, size);
		size--;
		tmp = tmp->next;
	}
	if (cmd->flags == T_WORD && !cmd->argv)
		cmd->flags = EMPTY;
	*holder = node;
}

void	divide(t_list **inputs, t_btree **tree, t_hashtable **env)
{
	t_btree		*holder;
	size_t		size;

	holder = NULL;
	size = 0;
	while (*inputs)
	{
		is_between_p(inputs, tree, env);
		if (!(*inputs))
			break ;
		size = until_next_op(inputs);
		create_tree(inputs, &holder, size, env);
		new_branch((t_wd_desc *)(*inputs)->content, holder, tree);
		while (size > 0)
		{
			(*inputs) = (*inputs)->next;
			size--;
		}
		holder = NULL;
	}
}
