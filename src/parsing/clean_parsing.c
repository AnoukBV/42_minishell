/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:56:53 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/09 12:36:16 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_wddesc(void *word)
{
	t_wd_desc	*del;

	if (!word)
		return ;
	del = (t_wd_desc *)word;
	free(del->word);
	del->word = NULL;
	free(del);
	del = NULL;
}

void	free_before_id(t_list *inputs, size_t in_nb)
{
	size_t	i;

	i = 0;
	if (!inputs)
		return ;
	while (i < in_nb)
	{
		ft_lstclear(&inputs, &del_wddesc);
		i++;
	}
}
