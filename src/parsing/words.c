/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:17:49 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/28 14:45:16 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	new_word(t_list **list, char *str, size_t end, size_t start)
{
	t_wd_desc	*tok;

	if (start != end)
	{
		tok = new_wd_desc(0, ft_substr(str, start, end - start));
		ft_lstadd_back(list, ft_lstnew(tok));
	}
}

static size_t	new_metacharacter(t_list **list, char *str)
{
	size_t		i;
	t_wd_desc	*tok;

	i = 0;
	if (!ft_isspace(str[i]))
	{
		if (str[i + 1] && ft_strchr("<>", str[i]) && str[i + 1] == str[i])
			tok = new_wd_desc(0, ft_substr(&str[i], 0, 2));
		else
			tok = new_wd_desc(0, ft_substr(&str[i], 0, 1));
		if (ft_strchr("<>", tok->word[0]) && !ft_isspace(str[i - 1]))
			tok->flags += 3000;
		ft_lstadd_back(list, ft_lstnew(tok));
		if (tok->flags == 3000)
			undefault_fd_tok(list, &tok);
	}
	return (i);
}

static void	input_into_words(char *str, t_list **words_list)
{
	t_esc		esc_status;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	esc_status.is_quoted = false;
	while (str[i])
	{
		check_quote(&esc_status, &str[i]);
		if (ft_strchr("|<> \t", str[i]) \
			&& esc_status.is_quoted == false)
		{
			new_word(words_list, str, i, j);
			i += new_metacharacter(words_list, &str[i]);
			j = i + 1;
		}
		i++;
	}
	if (!ft_isspace(str[i - 1]))
		new_word(words_list, str, i, j);
}

void	check_quote(t_esc *esc_status, char *str)
{
	if (*str != '\'' && *str != '"')
		return;
	if (esc_status->is_quoted == false && ft_strchr("\'\"", str[0]) \
		&& ft_strlen(str) > 1 && ft_strchr(&str[1], str[0]))
	{
		esc_status->is_quoted = true;
		if (str[0] == '\'')
			esc_status->is_simplequote = true;
		else
			esc_status->is_simplequote = false;
//		return ;
	}
	else if (esc_status->is_quoted == false && ft_strchr("\'\"", str[0]) \
		&& ft_strlen(str) > 1 && !ft_strchr(&str[1], str[0]))
		esc_status->unclosed = true;
	else if (esc_status->is_quoted == false)
		return ;
//	else if ((esc_status->is_simplequote == true && str[0] == '\"') || \
//		(esc_status->is_simplequote == false && str[0] == '\''))
		//return ;
	//esc_status->is_quoted = false ;
}

void	break_into_words(t_list **inputs, char *inputs_array)
{
	*inputs = NULL;
	input_into_words(inputs_array, inputs);
}
