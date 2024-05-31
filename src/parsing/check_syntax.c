/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:21:00 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/31 10:14:42 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_err_prompt(char *token, t_list **inputs)
{
	printf("\n[syntax_err_prompt] inputs before stx exit: \n");
	print_unidentified_tokens(*inputs);
	ft_putstr_fd("minishell: syntax error near unexpected token `", 1);
	ft_putstr_fd(token, 1);
	ft_putstr_fd("'\n", 1);
	if (inputs)
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
	if ((ft_lstsize(*inputs) == 1 && curr->flags != T_WORD) || \
		(ft_lstsize(*inputs) == 2 && (curr->flags == T_RED_IN && \
		(int)((t_wd_desc *)check->next->content)->flags == T_RED_OUT)))
		syntax_err_prompt("newline", inputs);
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

void	unclosed_quotes(char *str)
{
	int	i;
	t_esc	status;

	status.is_quoted = false;
	status.unclosed = false;
	i = 0;
	while (str[i])
	{
		check_quote(&status, &str[i]);
		if (status.unclosed == true && status.is_simplequote == false)
		{
			free(str);
			syntax_err_prompt("\" --unclosed", NULL);
		}
		else if (status.unclosed == true && status.is_simplequote == true)
		{
			free(str);
			syntax_err_prompt("' --unclosed", NULL);
		}
		i++;
	}
}
