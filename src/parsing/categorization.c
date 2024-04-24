/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   categorization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:20:33 by aboulore          #+#    #+#             */
/*   Updated: 2024/04/24 13:42:42 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	word_or_operator(t_list **inputs)
{
	t_list	*tmp;
	t_wd_desc	*word;
	size_t	tk_nb;
	size_t	i;

	tk_nb = ft_lstsize(*inputs);
	i = 0;
	tmp = *inputs;
	while (i < tk_nb)
	{
		word = (t_wd_desc *)tmp->content;
		if (ft_strchr("|&<>()", word->word[0]))
			word->flags = 1;
		else
			word->flags = 0;
		tmp = tmp->next;
		i++;
	}
}
