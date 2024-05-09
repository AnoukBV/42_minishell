/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_delone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:37:34 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/09 12:38:18 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_delone(t_btree *tree, void (*del)(void *))
{
	if (tree)
		return ;
	if (del)
	  	del(tree->item);
	free(tree);
}
