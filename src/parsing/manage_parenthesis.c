/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_parenthesis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:43:20 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/01 14:07:50 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*isolate_new(t_list *start, t_list *end)
{
	t_list	*new;
	t_list	*tmp;
	t_wd_desc	*tok;

	new = NULL;
	tmp = start;
	while (tmp != end)
	{
		tok = (t_wd_desc *)tmp->content;
		ft_lstadd_back(&new, ft_lstnew(new_wd_desc(tok->flags, \
			ft_strdup(tok->word))));
		tmp = tmp->next;
	}
	return (new);
}

static t_bool	next_open_null(t_list *list)
{
	t_list	*tmp;
	t_wd_desc	*tok;

	tmp = list;
	while (tmp)
	{
		tok = (t_wd_desc *)tmp->content;
		if (tok->flags == T_CLOSE)
			return (false);
		else if (tok->flags == T_OPEN)
			break ;
		tmp = tmp->next;	
	}
	return (true);
}

static t_list	*seek_new_end(t_list *list)
{
	t_list	*end;
	t_wd_desc	*tok;

	end = list;
	while (1)
	{
		tok = (t_wd_desc *)end->content;
		if (tok->flags == T_CLOSE && next_open_null(end->next) == true)
			break ;
		end = end->next;
	}
	//*list = end;
	return (end);
}

void	is_between_p(t_list **inputs, t_btree **tree)
{
	t_list	*tmp;
	t_list	*tmp2;
	t_list	*new;

	if (((t_wd_desc *)(*inputs)->content)->flags != T_OPEN)
		return ;
	tmp = (*inputs)->next;
	tmp2 = seek_new_end(tmp);
	new = isolate_new(tmp, tmp2);
	divide(&new, tree);
	ft_lstclear(&new, &del_wddesc);
	*inputs = tmp2->next;
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
