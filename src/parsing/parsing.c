/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:33:37 by aboulore          #+#    #+#             */
/*   Updated: 2024/04/25 09:37:18 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_quote_bis(t_esc *esc_status, char *str)
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
	esc_status->is_quoted = false ;	
	str[i] = '\n';
}

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

static void	*quotes_removal(void *content)
{
	t_wd_desc	*token;
	t_wd_desc	*old;
	t_esc		esc_status;
	char		*str;
	size_t		i;
	
	i = 0;
	old = (t_wd_desc *)content;
	token = new_wd_desc(old->flags, ft_strdup(old->word));
	str = token->word;
	if (ft_strchr("()|&<>", str[0]))
		return (token);
	esc_status.is_quoted = false;
	while (str[i])
	{
		check_quote_bis(&esc_status, &str[i]);
		if (esc_status.is_quoted == true && esc_status.is_simplequote \
			== false && str[i] == '$')
			token->flags += 500;
		i++;
	}
	token->word = trim_quotes(str);
	return (token);
}

void	parsing(char *str, t_list **inputs)
{
//	lexer
	t_list	*map;

	if (!str)
		return ;
	break_into_words(inputs, str); 
	word_or_operator(inputs);
	print_unidentified_tokens(*inputs); //DELETE
	map = ft_lstmap(*inputs, &quotes_removal, \
		&del_wddesc);
	ft_lstclear(inputs, del_wddesc);
	*inputs = map;
	printf("\nAfter quote removal\n");	//DELETE
	print_unidentified_tokens(*inputs); //DELETE

//	identification;

//	parser
}
