/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:56:53 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/07 20:21:09 by aboulore         ###   ########.fr       */
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
	//t_list	*tmp;
	//t_list	*tmp2;

	i = 0;
	if (!inputs)
		return ;
	while (i < in_nb)
	{
		ft_lstclear(&inputs, &del_wddesc);
	//	tmp2 = tmp;
	//	tmp = tmp->next;
	//	free(tmp2);
		i++;
	}
}

void	free_redirections(t_redir_list *list)
{
	if (!list)
		return ;
	while (list)
	{
		if (list->target_filename)
			free(list->target_filename);
		list = list->next;
	}
	free(list);
}

void	free_binary_tree(t_btree *del)
{
	t_btree		*left;
	t_btree		*right;
	t_command	*tree;

	if (!del)
		return ;
	tree = (t_command *)del->item;
	if (tree == NULL)
	{
		free(del);
		return ;
	}
	if (tree->argv && tree->is_argv == true)
		free_array_2d((char **)tree->argv);
	//else rec ?
	if (tree->command)
		free(tree->command);
	if (tree->redir_list)
		free_redirections(tree->redir_list);
	left = del->left;
	right = del->right;
	free(tree);
	free(del);
	free_binary_tree(right);
	free_binary_tree(left);
}
