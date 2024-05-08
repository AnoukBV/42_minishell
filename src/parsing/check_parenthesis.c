/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 12:08:46 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/08 17:41:36 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	check_number_parenth(t_list *list)
{
	t_list		*tmp;
	t_wd_desc	*tok;
	size_t		open;
	size_t		close;

	tmp = list;
	open = 0;
	close = 0;
	while (tmp)
	{
		tok = (t_wd_desc *)tmp->content;
		if (tok->flags == T_OPEN)
			open++;
		else if (tok->flags == T_CLOSE)
			close++;
		tmp = tmp->next;
	}
	if (open != close)
		return (false);
	return (true);
}

static void	redo_flags(t_list **list)
{
	t_list		*tmp;
	t_wd_desc	*tok;

	tmp = *list;
	while (tmp)
	{
		tok = (t_wd_desc *)tmp->content;
		if (tok->flags % 1000 > 700)
			tok->flags -= 700;
		if (tok->flags % 1000 > 300)
			tok->flags -= 300;
		tmp = tmp->next;
	}
}

static t_bool	seek_closing(t_list **list)
{
	t_list		*tmp;
	t_wd_desc	*tok;
	t_bool		closed;

	tmp = *list;
	closed = false;
	while (tmp)
	{
		tok = (t_wd_desc *)tmp->content;
		if (tok->flags == T_CLOSE && tok->flags < 700)
		{
			closed = true;
			tok->flags += 700;
			return (true);
		}
		tmp = tmp->next;
	}
	return (closed);
}

static t_bool	check_pairing_parenth(t_list *list)
{
	t_list		*tmp;
	t_list		*head;
	t_wd_desc	*tok;

	tmp = list;
	while (tmp)
	{
		tok = (t_wd_desc *)tmp->content;
		if (tok->flags == T_OPEN)
		{
			head = tmp->next;
			if (seek_closing(&head) == false)
				return (false);
		}
		tmp = tmp->next;
	}
	redo_flags(&list);
	return (true);
}

t_bool	check_validity_parenthesis(t_list *list)
{
	if (check_number_parenth(list) == false)
	{
		printf("because of numner\n");
		return (false);
	}
	if (check_pairing_parenth(list) == false)
	{
		printf("because of pairing\n");
		return (false);
	}
	//printf("valid parenth\n");
	return (true);
}
