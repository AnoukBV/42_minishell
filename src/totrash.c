/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   totrash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:54:38 by aboulore          #+#    #+#             */
/*   Updated: 2024/04/24 14:05:54 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_2d_array(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		ft_putstr("\nNEW_INPUT: ");
		ft_putstr(str[i]);
		i++;
	}
}

void	print_unidentified_tokens(t_list *inputs)
{
	size_t	j;
	size_t	size_input;
	t_list	*tmp;
	t_wd_desc	*word;

	tmp = inputs;
	printf("\nDATA BEFORE IDENTIFICATION\n");
	j = 0;
	size_input = ft_lstsize(tmp);
	while (j < size_input)
	{
		printf("\nTOKEN N°%zu = ", j);
		word = (t_wd_desc*)tmp->content;
		printf("%s\n", word->word);
		tmp = tmp->next;
		j++;
	}
	printf("\n");
}
