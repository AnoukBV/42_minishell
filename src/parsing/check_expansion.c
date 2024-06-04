/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:56:27 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/04 10:57:35 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	check_expansion(t_exp **expansion, char *str)
{
	t_exp			*exp_status;

	exp_status = *expansion;
	check_quote(exp_status->esc_status, str);
	if (*str == '$' && exp_status->is_exp_sim == false)
		return (true);
	else if (exp_status->is_exp_sim == true)
	{
		if ((ft_strlen(str) > 2 && ft_strchr("\'\"", str[1]) && str[2] \
			&& ft_strchr(&str[2], str[1])) || \
			(!ft_isalnum(str[0]) && str[0] != '_'))
			exp_status->is_exp_sim = false;
		return (exp_status->is_exp_sim);
	}
	else if (exp_status->is_exp_quo == true)
	{
		if ((str[0] == '\"' && exp_status->esc_status->is_quoted == false) || \
			(!ft_isalnum(str[0]) && str[0] != '_' && str[0] != '$'))
			exp_status->is_exp_quo = false;
		return (exp_status->is_exp_quo);
	}
	return (false);
}
