/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:33:37 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/04 11:20:40 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_isspace(char *str)
{
	size_t	i;
	t_esc	stat;

	i = 0;
	while (str[i] && (ft_isspace(str[i]) \
		&& is_space_esc(stat, str[i]) == false))
	{
		check_quote(&stat, &str[i]);
		i++;
	}
	return (i);
}

static void	divide(t_list **inputs, t_btree **tree, t_list **env)
{
	t_btree		*holder;
	t_list		*save;
	size_t		size;

	holder = NULL;
	size = 0;
	save = *inputs;
	while (*inputs)
	{
		if (!(*inputs))
			break ;
		size = until_next_op(inputs);
		create_tree(inputs, &holder, size, env);
		new_branch((t_wd_desc *)(*inputs)->content, holder, tree);
		while (size > 0)
		{
			(*inputs) = (*inputs)->next;
			size--;
		}
		holder = NULL;
	}
	ft_lstclear(&save, &del_wddesc);
}

int	parsing(char *str, t_list **inputs, t_list *env, t_pipeline **pipeline)
{
	t_btree		*tree;
	char		*res;

	if (unclosed_quotes(str) == 1)
		return (1);
	//printf("\n[parsing] str before trimming isspaces: BEG/%s/END\n", str);
	res = ft_strtrim(str, " \t");
	free(str);
	//printf("\n[parsing] str after trimming isspaces: BEG/%s/END\n", res);
	tree = NULL;
	break_into_words(inputs, res);
	free(res);
	word_or_operator(inputs);
	//print_unidentified_tokens(*inputs);
	expansion(inputs, env);
	//print_unidentified_tokens(*inputs);
	//printf("\n[parsing] (*inputs) before sec_tokenizing: %p\n", (*inputs));
	//print_unidentified_tokens(*inputs);
//	printf("\n[parsing] (*inputs)->next before sec_tokenizing: %p\n", (*inputs)->next);
	second_tokenizing(inputs);
	//print_unidentified_tokens(*inputs);
	if (syntax_errors(inputs) == 1)
		return (1);
	divide(inputs, &tree, &env);
	//printf("\n[parsing] here before quotes removal\n");
	//if (tree)
	//	quotes_removal(tree->item);
	btree_apply_prefix(tree, &quotes_removal);
	//printf("\n[parsing] here after quotes removal\n");
	//print_divided_cmds(tree, 0);
	//printf("\n[parsing] here before argv creation\n");
	btree_apply_prefix(tree, &create_argv);
	//printf("\n[parsing] here after argv creation\n");
	//printf("\n[parsing] here before fill_pipeline\n");
	fill_pipeline(pipeline, tree, env);
	//printf("\n[parsing] here after fill_pipeline\n");
	//printf("\n[parsing] here before clear tree\n");
	btree_clear_infix(tree, NULL);
	//printf("\n[parsing] here after clear tree\n");
	//printf("\n[parsing] final\n");
	//print_pipeline(*pipeline);
	return (0);
}
