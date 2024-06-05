/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:21:00 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/05 15:10:19 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	syntax_err_prompt(char *token, t_list **inputs, t_list **env)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	if (inputs != NULL)
		ft_lstclear(inputs, &del_wddesc);
	update_env_exit_code(env, 2);
	return (2);
}

static int	rest_of_syntax(t_list **ch, t_list **inputs, t_list **env)
{
	t_list		*check;
	t_wd_desc	*prev;
	t_wd_desc	*curr;

	check = *ch;
	curr = check->content;
	prev = curr;
	check = check->next;
	while (check)
	{
		curr = check->content;
		if ((curr->flags == T_PIPE && prev->flags == T_PIPE) || \
			((prev->flags == T_RED_OUT || prev->flags == T_RED_IN \
			|| prev->flags == T_APP_OUT || prev->flags == T_APP_IN ) \
			&& curr->flags != T_WORD))
			return (syntax_err_prompt(curr->word, inputs, env));
		else if (curr->flags != T_WORD && check->next == NULL)
			return (syntax_err_prompt("newline", inputs, env));
		prev = curr;
		check = check->next;
	}
	return (0);
}

int	syntax_errors(t_list **inputs, t_list **env)
{
	t_list		*check;
	t_wd_desc	*curr;
	int			exit;

	check = *inputs;
	if (!check)
		return (1);
	curr = check->content;
	if (curr->flags == T_PIPE)
		return (syntax_err_prompt(curr->word, inputs, env));
	else if ((ft_lstsize(*inputs) == 1 && curr->flags != T_WORD) || \
		(ft_lstsize(*inputs) == 2 && (curr->flags == T_RED_IN && \
		(int)((t_wd_desc *)check->next->content)->flags == T_RED_OUT)))
		return (syntax_err_prompt("newline", inputs, env));
	exit = rest_of_syntax(&check, inputs, env);
	return (exit);
}
