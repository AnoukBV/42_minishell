/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   categorization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:20:33 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/02 08:52:31 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	token_type(t_wd_desc **word)
{
	char	*tmp;

	tmp = (*word)->word;
	if (!ft_strncmp(tmp, "&&", 2))
		(*word)->flags = T_AND;
	else if (!ft_strncmp(tmp, "||", 2))
		(*word)->flags = T_OR;
	else if (!ft_strncmp(tmp, "|", 1))
		(*word)->flags = T_PIPE;
	else if (!ft_strncmp(tmp, "(", 1))
		(*word)->flags = T_OPEN;
	else if (!ft_strncmp(tmp, ")", 1))
		(*word)->flags = T_CLOSE;
	else if (!ft_strncmp(tmp, "<<", 2) \
		&& ft_strlen(tmp) == 2)
		(*word)->flags += T_APP_OUT;
	else if (!ft_strncmp(tmp, "<", 1))
		(*word)->flags += T_RED_OUT;
	else if (!ft_strncmp(tmp, ">>", 2) && \
		ft_strlen(tmp) == 2)
		(*word)->flags += T_APP_IN;
	else if (!ft_strncmp(tmp, ">", 1))
		(*word)->flags += T_RED_IN;
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
