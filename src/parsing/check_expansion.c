/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:56:27 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/28 14:40:05 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static t_bool	exp_between_quotes(char *str)
{
	size_t	i;
	char	*block;

	i = 1;
	block = ft_strchr(&str[i], '\"');
	while (&str[i] != block && str[i])
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}
*/
static t_bool	activate_exp(char *c, t_exp **expansion, t_bool save_q)
{
	t_exp	*exp_status;

	exp_status = *expansion;
	//if (save_q)
	(void)c;
	(void)save_q;
	return (true);
}

t_bool	check_expansion(t_exp **expansion, char *str)
{
	static t_bool	save_q;
	t_exp			*exp_status;

	exp_status = *expansion;
	save_q = exp_status->esc_status->is_quoted;
	check_quote(exp_status->esc_status, str);
	if (*str == '$' && exp_status->is_exp_sim == false)
		return (activate_exp(str, expansion, save_q));
	else if (exp_status->is_exp_sim == true)
	{
		if ((ft_strlen(str) > 2 && ft_strchr("\'\"", str[1]) && str[2] \
			&& ft_strchr(&str[2], str[1])) || (!ft_isalnum(str[0]) && str[0] != '_'))
			exp_status->is_exp_sim = false;
		return (exp_status->is_exp_sim);
	}
	else if (exp_status->is_exp_quo == true)
	{
		if ((str[0] == '\"' && exp_status->esc_status->is_quoted == false) || \
			/*(ft_strchr(&str[2], str[1])) || */(!ft_isalnum(str[0]) && str[0] != '_' && str[0] != '$'))
		{
			exp_status->is_exp_quo = false;
			printf("icizzzzzzz\n");
		}
		return (exp_status->is_exp_quo);
	}
	return (false);
}
