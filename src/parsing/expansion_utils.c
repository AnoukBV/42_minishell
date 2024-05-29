/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:07:52 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/29 17:33:09 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_word_bis(t_list **node)

void	space_break(t_list **node, char *str)
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
		if (ft_strchr(" \t", str[i]) \
			&& esc_status.is_quoted == false)
		{
			new_word_bis(node, str, i, j);
			j = i + 1;
		}
		i++;
	}
	if (!ft_isspace(str[i - 1]))
		new_word(words_list, str, i, j);
}

void	second_tokenizing(t_list **inputs)
{
	t_list	*tmp;
	t_wd_desc	*tok;

	tmp = *inputs;
	while (tmp)
	{
		tok = (t_wd_desc *)tmp->content;
		if (tok->flags == T_WORD)
			space_breaking(&tmp, tok->word);
		tmp = tmp->next;
	}
}

char	*join_after_expansion(t_list **splitted_token)
{
	t_list	*tmp;
	char	*save;
	char	*new;

	tmp = *splitted_token;
	new = "\0";
	while (tmp)
	{
		save = ft_strdup(new);
	//	printf("\n[join_after_expansion] save(str to be added to the final str): %s\n", save);
		new = ft_strjoin(save, (char *)tmp->content);
	//	printf("\n[join_after_expansion] new(final str): %s\n", new);
		free(save);
		save = NULL;
		tmp = tmp->next;
	}
	if (*new == '\0')
		new = NULL;
	ft_lstclear(splitted_token, free);
	return (new);
}

void	init_tracker(t_exp **exp_status)
{
	*exp_status = malloc(sizeof(t_exp));
	if (!(*exp_status))
		return ;
	(*exp_status)->esc_status = malloc(sizeof(t_esc));
	if (!(*exp_status)->esc_status)
		return ;
	(*exp_status)->esc_status->is_quoted = false;
	(*exp_status)->is_exp_sim = false;
	(*exp_status)->is_exp_quo = false;
}
