/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:07:52 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/30 09:30:03 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*space_knitting(char **split, t_list **curr)
{
	size_t	i;
	t_list	*tmp;
	t_list	*new;

	i = 1;
	tmp = *curr;
	tmp->content = new_wd_desc(T_WORD, split[0]);
	while (split[i])
	{
		new = ft_lstnew(new_wd_desc(T_WORD, split[i]));
		new->next = tmp->next;
		tmp->next = new;
		tmp = new;
		i++;
	}
	return (tmp);
}

static t_list	*space_break(t_list **node, char *str)
{
	char	**split;
	t_list	*save;

	split = ft_esc_split(str, " \t");
	save = space_knitting(split, node);
	free(split);
	return (save);
}

void	second_tokenizing(t_list **inputs)
{
	t_list	*tmp;
	t_wd_desc	*tok;

	tmp = *inputs;
	while (tmp)
	{
		//printf("\n[second_tokenizing] tmp before space_break: %p\n", tmp);
		//printf("\n[second_tokenizing] tmp->next before space_break: %p\n", tmp->next);
		tok = (t_wd_desc *)tmp->content;
		if (tok->flags == T_WORD)
			tmp = space_break(&tmp, tok->word);
		//printf("\n[second_tokenizing] tmp after space_break(might have changed): %p\n", tmp);
		//printf("\n[second_tokenizing] tmp->next after space_break(shouldn't have changed): %p\n", tmp->next);
		if (tmp)
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
