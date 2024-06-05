/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_unclosed_ambiguous.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:17:29 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/05 14:23:18 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quotes_err_prompt(char *token, t_list **env)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	update_env_exit_code(env, 1);
	return (1);
}

int	red_experr_prompt(char *token, t_list **inputs, t_list **env)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(token, 1);
	ft_putstr_fd(": ambiguous redirect\n", 1);
	if (inputs)
		ft_lstclear(inputs, &del_wddesc);
	update_env_exit_code(env, 2);
	return (2);
}

int	unclosed_quotes(char *str, t_list **env)
{
	int		i;
	t_esc	status;

	status.is_quoted = false;
	status.is_simplequote = false;
	status.unclosed = false;
	i = 0;
	while (str[i])
	{
		check_quote(&status, &str[i]);
		if (status.unclosed == true && str[i] == '"')
		{
			free(str);
			return (quotes_err_prompt("\" --unclosed", env));
		}
		else if (status.unclosed == true && str[i] == '\'')
		{
			free(str);
			return (quotes_err_prompt("' --unclosed", env));
		}
		i++;
	}
	return (0);
}
