/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:52:07 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/04 10:54:22 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*trim_quotes(char *str)
{
	char	*new;
	char	**array;

	if (ft_strlen(str) == 2 && str[0] == '\n' && str[1] == '\n')
	{
		free(str);
		return (ft_strdup(""));
	}
	array = ft_split(str, '\n');
	new = ft_superjoin(array, NULL);
	free_array_2d(array);
	free(str);
	//printf("\n[trim_quotes] new: %s\n", new);
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

static void	redir_exec_removal(char **token)
{
	t_esc		esc_status;
	size_t		i;
	char		*str;
	char		*item;

	i = 0;
	item = *token;
	if (ft_strchr("|<>", item[0]) || (!ft_strchr(item, \
		'\'') && !ft_strchr(item, '"')))
		return ;
	esc_status.is_quoted = false;
	while (item[i])
	{
		check_quote_bis(&esc_status, &item[i]);
		i++;
	}
	str = ft_strdup(item);
	item = trim_quotes(str);
	*token = item;
}

static void	ft_redirlstiter(t_redir_list *lst, void (f)(char **))
{
	while (lst && (*f))
	{
		f(&lst->target_filename);
		lst = lst->next;
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

void	quotes_removal(void *content)
{
	t_command	*cmd;
	t_list		*argv;
	t_list		*save;
	t_list		*map;

	//printf("\n[quotes_removal] here at very beginning\n");
	cmd = (t_command *)content;
	//printf("\n[quotes_removal] in beginning of function\n");
	if (cmd->is_argv == true && cmd->argv)
	{
	//	printf("\n[quotes_removal] in if statement\n");
		argv = (t_list *)cmd->argv;
		if (!argv)
			return ;
	//	printf("\n[quotes_removal] argv not considered empty\n");
		save = argv;
		map = ft_lstmap(argv, &exec_removal, &del_wddesc);
		ft_lstclear(&save, &del_wddesc);
		cmd->argv = map;
	}
	if (cmd->redir_list)
		ft_redirlstiter(cmd->redir_list, &redir_exec_removal);
}