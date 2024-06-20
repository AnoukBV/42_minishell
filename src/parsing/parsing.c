/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:33:37 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/11 12:59:25 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_isspace(char *str)
{
	size_t	i;
	t_esc	stat;

	i = 0;
	stat.is_quoted = false;
	while (str[i] && (ft_isspace(str[i]) \
		&& is_space_esc(stat, str[i]) == false))
	{
		check_quote(&stat, &str[i]);
		i++;
	}
	if (i == ft_strlen(str))
	{
		free(str);
		return (1);
	}
	return (0);
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
		}
		tmp = tmp->next;
	}
}

int	parsing(char *str, t_list **inputs, t_list *env, t_pipeline **pipeline)
{
	t_btree		*tree;
	char		*res;

	if (unclosed_quotes(str, &env) == 1 || count_isspace(str) == 1)
		return (1);
	res = ft_strtrim(str, " \t");
	free(str);
	tree = NULL;
	break_into_words(inputs, res);
	free(res);
	word_or_operator(inputs);
	if (expansion(inputs, env) == 1)
		return (1);
	second_tokenizing(inputs);
	if (syntax_errors(inputs, &env) == 1)
		return (1);
	heredoc_flag(inputs);
	divide(inputs, &tree, &env);
	btree_apply_prefix(tree, &quotes_removal);
	btree_apply_prefix(tree, &create_argv);
	if (fill_pipeline(pipeline, tree, env) == -1)
		return (1);
	return (0);
}
