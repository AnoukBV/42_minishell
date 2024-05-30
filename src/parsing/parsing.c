/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:33:37 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/30 16:43:23 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*trim_quotes(char *str)
{
	char	*new;
	char	**array;

	if (ft_strlen(str) == 2 && str[0] == '\n' && str[1] == '\n')
		return (ft_strdup(""));
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
	if (!token->word)
		return (token);
	if (ft_strchr("|<>", token->word[0]) || (!ft_strchr(token->word, \
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
	t_list		*map = NULL;

	printf("\n[quotes_removal] here at very beginning\n");
	cmd = (t_command *)content;
	printf("\n[quotes_removal] in beginning of function\n");
	if (cmd->is_argv == true && cmd->argv)
	{
		printf("\n[quotes_removal] in if statement\n");
		argv = (t_list *)cmd->argv;
		if (!argv)
			return ;
		printf("\n[quotes_removal] argv not considered empty\n");
		save = argv;
		map = ft_lstmap(argv, &exec_removal, &del_wddesc);
		ft_lstclear(&save, &del_wddesc);
		cmd->argv = map;
	}
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

size_t	count_isspace(char *str)
{
	size_t	i;
	t_esc	stat;

	i = 0;
	while (str[i] && (ft_isspace(str[i]) && is_space_esc(stat, str[i]) == false))
	{
		check_quote(&stat, &str[i]);
		i++;
	}
	return (i);
}
/*
size_t	add_and_skip(char *str, char *new, t_esc *stat, size_t prev)
{
	size_t	i;

	i = 0;
	if (new && prev != 0 && new[i + 1])
		*new = ' ';
	while (str[i] && (ft_isspace(str[i]) && is_space_esc(*stat, str[i]) == false))
	{
		check_quote(stat, &str[i]);
		i++;
	}
	i -= 1;
	return (i);
}

char	*trim_isspace(char *str, int ditch)
{
	char *new;
	size_t	i;
	t_esc	stat;

	i = 0;
	stat.is_quoted = false;
	new = ft_calloc(sizeof(char), (ft_strlen(str) - ditch + 1));
	if (!new)
		return (NULL);
	while (str[i])
	{
		check_quote(&stat, &str[i]);
		if (!ft_isspace(str[i]) || (ft_isspace(str[i]) && is_space_esc(stat, str[i]) == true))
			new[ft_strlen(new)] = str[i];
		else if (is_space_esc(stat, str[i]) == false)
			i += add_and_skip(&str[i], &new[ft_strlen(new)], &stat, i);
		i++;
	}
	new[ft_strlen(new)] = '\0';
	free(str);
	return (new);
}

char	*skip_isspace(char *str)
{
	int	i;
	int	ditch;
	t_esc	stat;
	char	*new;

	i = 0;
	stat.is_quoted = false;
	ditch = 0;
	while (str[i])
	{
		check_quote(&stat, &str[i]);
		if (ft_isspace(str[i]) && is_space_esc(stat, str[i]) == false)
		{
			i++;
			while (str[i] && ft_isspace(str[i]) && is_space_esc(stat, str[i]) == false)
			{
				ditch++;
				i++;
			}
		}
		else
			i++;
	}
	new = trim_isspace(str, ditch);
	return (new);
}
*/
t_pipeline	*parsing(char *str, t_list **inputs, t_list *env)
{
	t_pipeline	*pipeline;
	t_btree		*tree;
	
	unclosed_quotes(str);
	printf("\n[parsing] str before trimming isspaces: BEG/%s/END\n", str);
	str = ft_strtrim(str, " \t");
	printf("\n[parsing] str after trimming isspaces: BEG/%s/END\n", str);
	tree = NULL;
	break_into_words(inputs, str);
	free(str);
	word_or_operator(inputs);
	print_unidentified_tokens(*inputs);
	expansion(inputs, env);
	print_unidentified_tokens(*inputs);
//	printf("\n[parsing] (*inputs) before sec_tokenizing: %p\n", (*inputs));
//	printf("\n[parsing] (*inputs)->next before sec_tokenizing: %p\n", (*inputs)->next);
	second_tokenizing(inputs);	
	print_unidentified_tokens(*inputs);

	syntax_errors(inputs);
	divide(inputs, &tree, &env);
	printf("\n[parsing] here before quotes removal\n");
	//if (tree)
	//	quotes_removal(tree->item);
	btree_apply_prefix(tree, &quotes_removal);
	printf("\n[parsing] here after quotes removal\n");
	print_divided_cmds(tree, 0);
	printf("\n[parsing] here before argv creation\n");
	btree_apply_prefix(tree, &create_argv);
	printf("\n[parsing] here after argv creation\n");
	printf("\n[parsing] here before fill_pipeline\n");
	fill_pipeline(&pipeline, tree, env);
	printf("\n[parsing] here after fill_pipeline\n");
	printf("\n[parsing] here before clear tree\n");
	btree_clear_infix(tree, NULL);
	printf("\n[parsing] here after clear tree\n");
	return (pipeline);
}
