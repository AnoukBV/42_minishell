/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:56:53 by aboulore          #+#    #+#             */
/*   Updated: 2024/04/24 19:05:28 by aboulore         ###   ########.fr       */
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
	t_list	*del;
	//t_list	*tmp;
	//t_list	*tmp2;

	i = 0;
	del = inputs;
	if (!del)
		return ;
	while (i < in_nb)
	{
		ft_lstclear(&del, &del_wddesc);
	//	tmp2 = tmp;
	//	tmp = tmp->next;
	//	free(tmp2);
		i++;
	}
}
