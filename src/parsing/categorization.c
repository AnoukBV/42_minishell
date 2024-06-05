/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   categorization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:20:33 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/05 12:23:20 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	token_type(t_wd_desc **word)
{
	char	*tmp;

	tmp = (*word)->word;
	if (!ft_strncmp(tmp, "|", 1))
		(*word)->flags = T_PIPE;
	else if (!ft_strncmp(tmp, "<<", 2) \
		&& ft_strlen(tmp) == 2)
		(*word)->flags += T_APP_IN;
	else if (!ft_strncmp(tmp, "<", 1))
		(*word)->flags += T_RED_IN;
	else if (!ft_strncmp(tmp, ">>", 2) && \
		ft_strlen(tmp) == 2)
		(*word)->flags += T_APP_OUT;
	else if (!ft_strncmp(tmp, ">", 1))
		(*word)->flags += T_RED_OUT;
	else
		(*word)->flags = T_WORD;
}

void	word_or_operator(t_list **inputs)
{
	t_list		*tmp;
	t_wd_desc	*word;
	size_t		tk_nb;
	size_t		i;

	tk_nb = ft_lstsize(*inputs);
	i = 0;
	tmp = *inputs;
	while (i < tk_nb)
	{
		word = (t_wd_desc *)tmp->content;
		token_type(&word);
		tmp = tmp->next;
		i++;
	}
}

void	init_tracker(t_exp **exp_status)
{
	*exp_status = malloc(sizeof(t_exp));
	if (!(*exp_status))
		malloc_error();
	(*exp_status)->esc_status = malloc(sizeof(t_esc));
	if (!(*exp_status)->esc_status)
		malloc_error();
	(*exp_status)->esc_status->is_quoted = false;
	(*exp_status)->is_exp_sim = false;
	(*exp_status)->is_exp_quo = false;
}

void	check_quote_bis(t_esc *esc_status, char *str)
{
	size_t	i;

	i = 0;
	if (!ft_strchr("\'\"", str[i]))
		return ;
	if (esc_status->is_quoted == false && ft_strchr("\'\"", str[i]) \
		&& ft_strchr(&str[i + 1], str[i]) && str[i + 1] != 0)
	{
		esc_status->is_quoted = true;
		if (str[i] == '\'')
			esc_status->is_simplequote = true;
		else
			esc_status->is_simplequote = false;
		str[i] = '\n';
		return ;
	}
	else if (esc_status->is_quoted == false)
		return ;
	else if ((esc_status->is_simplequote == true && str[i] == '\"') || \
		(esc_status->is_simplequote == false && str[i] == '\''))
		return ;
	esc_status->is_quoted = false;
	str[i] = '\n';
}
