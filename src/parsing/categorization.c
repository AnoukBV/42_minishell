/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   categorization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:20:33 by aboulore          #+#    #+#             */
/*   Updated: 2024/04/24 13:12:09 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	word_or_operator(t_list **inputs)
{
	t_list	*tmp;
	t_list	*tmp2;
	size_t	tk_nb;
	size_t	i;

	tk_nb = ft_lstsize(*inputs);
	i = 0;
	tmp = *inputs;
	while (i < tk_nb)
	{
		tmp2 = tmp->content;
		if (ft_strchr("|&<>()", tmp2->word))
			tmp2->flag = 1;
		else
			tmp2->flag = 0;
		tmp = tmp->next;
		i++;
	}
}
