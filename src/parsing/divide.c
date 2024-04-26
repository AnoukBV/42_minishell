/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:41:22 by aboulore          #+#    #+#             */
/*   Updated: 2024/04/26 13:32:57 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static t_list	*ft_sublst(t_list *start, t_list *end)
{
	t_list *tmp;
	t_list *new;

	tmp = start;
	new = NULL;
	if (!start)
		return (NULL);
	while (tmp && tmp != end)
	{
		ft_lstadd_back(&new, ft_lstnew(tmp->content));
		tmp = tmp->next;
	}
	return (new);
} */
/*
static t_list	*seek_closing(t_list	**inputs, t_list **new)
{
	t_list	*tmp;
	t_list	*head;
	t_wd_desc	*tok;

	tmp = *inputs;
	(void)new;
	while (tmp)
	{
		tok = (t_wd_desc *)tmp->content;
		if (tok->word[0] == ')' && tok->flags != 0)
		{
			tok->flags = 3;
			head = ft_lstnew(ft_sublst(*inputs, tmp->next));
			//printf("helloe\n\n");
			//print_unidentified_tokens((t_listhead); //DELETE
			//ft_lstadd_back(new, head);
			*inputs = tmp;
			return ((t_list *)head->content);
		}
		tmp = tmp->next;
	}
	return (NULL);
}*/
/*
static t_bool	between_brackets(t_list	**inputs, t_list **new)
{
	t_list		*tmp;
	t_wd_desc	*tok;
	t_wd_desc	*tok2;

	tmp = *inputs;
	while (tmp)
	{
		tok = (t_wd_desc *)tmp->content;
		tok2 = (t_wd_desc *)tmp->next->content;
		if ((tok->word[0] == '(' || (ft_strchr("|&", tok->word[0]) \
			&& tok2->word[0] == '(')) && tok->flags != 0)
		{
			if (seek_closing(&tmp, new) == false)
			{
				printf("syntaxerr\n");
				return (false);
			}
			else
			{
				if (tok->word[0] == '(') 
					tok->flags = 2;
				else
					tok2->flags = 2;
				*inputs = tmp->next;
				printf("in between brackets\n");
				print_unidentified_tokens(*inputs); //DELETE
				return (true);
			}
		}
		tmp = tmp->next;
	}
	return (false);
}

*/
/*

static void	create_tree(t_btree **tree, t_list **inputs)
{
	t_btree	*node;
	t_list	*tmp;
	t_list	*head;
	t_wd_desc	*tok;

	tmp = *inputs;
	head = tmp;
	while (tmp)
	{
		tok = (t_wd_desc *)tmp->content;
		if (tok->flags == PIPE)
		{
			node = btree_create_node(tmp);
			node->left = btree_create_node(head);
			node->right = bree_create_node
		}
		tmp = tmp->next;
	}
	*tree = node->left;
}

void	divide(t_list **inputs, t_list **new)
{
		t_list	*tmp;
		t_btree	*tree;

		(void)new;
		tree = NULL;
		tmp = *inputs;
		control_operator(&tmp);
		create_tree(&tree, inputs);
}*/
