/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:33:37 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/05 12:09:00 by aboulore         ###   ########.fr       */
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

void	heredoc_flag(t_list **inputs)
{
	t_wd_desc	*tok;
	t_wd_desc	*next;
	t_list		*tmp;

	tmp = *inputs;
	while (tmp)
	{
		tok = tmp->content;
		if (tok->flags == T_APP_IN)
		{
			next = tmp->next->content;
			if (next->word[0] == '"' || next->word[0] == '\'')
				tok->flags += 100;
				//printf("wowow");
		}
		tmp = tmp->next;
	}
}

int	parsing(char *str, t_list **inputs, t_list *env, t_pipeline **pipeline)
{
	t_btree		*tree;
	char		*res;

	if (unclosed_quotes(str, &env) == 1)
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
	if (expansion(inputs, env) == 1)
		return (1);
	print_unidentified_tokens(*inputs);
	//printf("\n[parsing] (*inputs) before sec_tokenizing: %p\n", (*inputs));
	//print_unidentified_tokens(*inputs);
//	printf("\n[parsing] (*inputs)->next before sec_tokenizing: %p\n", (*inputs)->next);
	second_tokenizing(inputs);
	print_unidentified_tokens(*inputs);
	if (syntax_errors(inputs, &env) == 1)
		return (1);
	heredoc_flag(inputs);
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
	if (fill_pipeline(pipeline, tree, env) == -1)
	{
		btree_clear_infix(tree, NULL);
		return (1);
	}
	//printf("\n[parsing] here after fill_pipeline\n");
	//printf("\n[parsing] here before clear tree\n");
	btree_clear_infix(tree, NULL);
	//printf("\n[parsing] here after clear tree\n");
	printf("\n[parsing] final\n");
	print_pipeline(*pipeline);
	return (0);
}
