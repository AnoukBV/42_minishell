/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_clear_infix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:36:31 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/09 14:47:35 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_clear_infix(t_btree *root, void (*del)(void *))
{
	t_btree	*right;

	right = NULL;
	if (!root)
		return ;
	if (root->left)
		btree_clear_infix(root->left, del);
	if (root->right)
		right = root->right;
	btree_delone(root, del);
	if (right)
		btree_clear_infix(right, del);
}
