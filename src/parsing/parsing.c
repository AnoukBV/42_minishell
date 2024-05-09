/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:33:37 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/09 16:01:41 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*trim_quotes(char *str)
{
	char	*new;
	char	**array;

	array = ft_split(str, '\n');
	new = ft_superjoin(array, NULL);
	free_array_2d(array);
	free(str);
	return (new);
}

static void	*exec_removal(void *item)
{
	t_wd_desc	*token;
	t_wd_desc	*old;
	t_esc		esc_status;
	char		*str;
	size_t		i;

	i = 0;
	old = (t_wd_desc *)item;
	token = new_wd_desc(old->flags, ft_strdup(old->word));
	if (ft_strchr("()|&<>", token->word[0]) || (!ft_strchr(token->word, \
		'\'') && !ft_strchr(token->word, '"')))
		return (token);
	str = token->word;
	esc_status.is_quoted = false;
	while (str[i])
	{
		check_quote_bis(&esc_status, &str[i]);
		i++;
	}
	token->word = trim_quotes(str);
	return (token);
}

static void	quotes_removal(void *content)
{
	t_command	*cmd;
	t_list		*argv;
	t_list		*save;
	t_list		*map;

	cmd = (t_command *)content;
	if (cmd->is_argv == true)
	{
		argv = (t_list *)cmd->argv;
		save = argv;
		map = ft_lstmap(argv, &exec_removal, &del_wddesc);
		ft_lstclear(&save, &del_wddesc);
		cmd->argv = map;
	}
	//else
}

void	check_quote_bis(t_esc *esc_status, char *str)
{
	size_t	i;

	i = 0;
	if (!ft_strchr("\'\"", str[i]))
		return ;
	if (esc_status->is_quoted == false && ft_strchr("\'\"", str[i]) \
		&& ft_strchr(&str[i + 1], str[i]) && str[i + 1] != 0)
	{
		esc_status->is_quoted = true;
		if (str[i] == '\'')
			esc_status->is_simplequote = true;
		else
			esc_status->is_simplequote = false;
		str[i] = '\n';
		return ;
	}
	else if (esc_status->is_quoted == false)
		return ;
	else if ((esc_status->is_simplequote == true && str[i] == '\"') || \
		(esc_status->is_simplequote == false && str[i] == '\''))
		return ;
	esc_status->is_quoted = false;
	str[i] = '\n';
}

t_pipeline	*parsing(char *str, t_list **inputs, t_hashtable *env)
{
	t_pipeline	*pipeline;
	t_btree		*tree;

	if (!str)
		return (NULL);
	tree = NULL;
	break_into_words(inputs, str);
	word_or_operator(inputs);
	if (check_validity_parenthesis(*inputs) == false)
	{
		//ft_putstr_fd("ERROR PARENTHESIS\n", 2);
		return (NULL);
	}
	divide(inputs, &tree, &env);
	//ft_lstclear(inputs, &del_wddesc);
	btree_apply_prefix(tree, &expansion);
	btree_apply_prefix(tree, &quotes_removal);
	btree_apply_prefix(tree, &create_argv);
	fill_pipeline(&pipeline, tree, env);
	btree_clear_infix(tree, NULL);
	return (pipeline);
}
