/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:21:00 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/03 13:16:12 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	syntax_err_prompt(char *token, t_list **inputs)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	if (inputs != NULL)
		ft_lstclear(inputs, &del_wddesc);
	g_status = 2;
//	rl_signals_handler(SIGINT);
	return (1);
}
/*
void	red_experr_prompt(char *token, t_list **inputs)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(token, 1);
	ft_putstr_fd(": ambiguous redirect:\n", 1);
	free(token);
	if (inputs)
		ft_lstclear(inputs, &del_wddesc);
	exit(2);
}
*/
int	syntax_errors(t_list **inputs)
{
	t_list		*check;
	t_wd_desc	*prev;
	t_wd_desc	*curr;

	check = *inputs;
	if (!check)
		return (1);
	curr = check->content;
	if (curr->flags == T_PIPE)
		return (syntax_err_prompt(curr->word, inputs));
	else if ((ft_lstsize(*inputs) == 1 && curr->flags != T_WORD) || \
		(ft_lstsize(*inputs) == 2 && (curr->flags == T_RED_IN && \
		(int)((t_wd_desc *)check->next->content)->flags == T_RED_OUT)))
		return (syntax_err_prompt("newline", inputs));
	
	prev = curr;
	check = check->next;
	while (check)
	{
		curr = check->content;
		if ((curr->flags == T_PIPE && prev->flags == T_PIPE) || \
			((prev->flags == T_RED_OUT || prev->flags == T_RED_IN || prev->flags == T_APP_OUT) && curr->flags != T_WORD))
			return (syntax_err_prompt(curr->word, inputs));
		else if (curr->flags != T_WORD && check->next == NULL)
			return (syntax_err_prompt("newline", inputs));
		prev = curr;
		check = check->next;
	}
	return (0);
}

int	quotes_err_prompt(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	g_status = 2;
//	rl_signals_handler(SIGINT);
	return (1);
}

int	unclosed_quotes(char *str)
{
	int	i;
	t_esc	status;

	status.is_quoted = false;
	status.is_simplequote = false;
	status.unclosed = false;
	i = 0;
	while (str[i])
	{
		check_quote(&status, &str[i]);
		if (status.unclosed == true && status.is_simplequote == false)
		{
			free(str);
			return (quotes_err_prompt("\" --unclosed"));
		}
		else if (status.unclosed == true && status.is_simplequote == true)
		{
			free(str);
			return (quotes_err_prompt("' --unclosed"));
		}
		i++;
	}
	return (0);
}
