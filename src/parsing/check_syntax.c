/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:21:00 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/15 19:02:34 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_err_prompt(char *token, t_list **inputs)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 1);
	ft_putstr_fd(token, 1);
	ft_putstr_fd("'\n", 1);
	ft_lstclear(inputs, &del_wddesc);
	exit(2);
}

void	syntax_errors(t_list **inputs)
{
	t_list		*check;
	t_wd_desc	*prev;
	t_wd_desc	*curr;

	check = *inputs;
	if (!check)
		return ;
	curr = check->content;
	if (curr->flags == T_PIPE)
		syntax_err_prompt(curr->word, inputs);
	prev = curr;
	check = check->next;
	while (check)
	{
		curr = check->content;
		if (prev->flags != 0 && curr->flags != 0)
			syntax_err_prompt(curr->word, inputs);
		prev = curr;
		check = check->next;
	}
}
