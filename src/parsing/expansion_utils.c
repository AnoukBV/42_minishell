/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:07:52 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/03 14:52:01 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*space_knitting(char **split, t_list **curr, t_list **prev)
{
	size_t	i;
	t_list	*tmp;
	t_wd_desc	*res;
	t_list	*new;

	i = 1;
	tmp = *curr;
	if (!split[0])
	{
		res = tmp->content;
		*curr = tmp->next;
		(*prev)->next = *curr;
		free(res);
		free(tmp);
		//printf("\n[space_knitting] size of split when node to be deleted: %zu\n", ft_arrlen(split));
		return (*prev);
	}
	
	res = tmp->content;
	tmp->content = NULL;
	tmp->content = new_wd_desc(T_WORD, split[0]);
	free(res);
	while (split[i])
	{
		if (count_isspace(split[i]) != ft_strlen(split[i]) || !split[i])
		{
			new = ft_lstnew(new_wd_desc(T_WORD, split[i]));
			new->next = tmp->next;
			tmp->next = new;
			tmp = new;
		}
		i++;
	}
	return (tmp);
}

static t_list	*space_break(t_list **node, t_list **prev, char *str)
{
	char	**split;
	t_list	*save;

	//printf("\n[space_break] char *str before esc_split: %s\n", str);
	split = ft_esc_split(str, " \t");
	save = space_knitting(split, node, prev);
	free(split);
	return (save);
}

void	second_tokenizing(t_list **inputs)
{
	t_list	*tmp;
	t_list	*prev;
	t_wd_desc	*tok;

	tmp = *inputs;
	while (tmp)
	{
		//printf("\n[second_tokenizing] tmp before space_break: %p\n", tmp);
		//printf("\n[second_tokenizing] tmp->next before space_break: %p\n", tmp->next);
		tok = (t_wd_desc *)tmp->content;
		if (tok->flags == T_WORD)
			tmp = space_break(&tmp, &prev, tok->word);
		//printf("\n[second_tokenizing] tmp after space_break(might have changed): %p\n", tmp);
		//printf("\n[second_tokenizing] tmp->next after space_break(shouldn't have changed): %p\n", tmp->next);
		if (tmp)
		{
			prev =tmp;
			tmp = tmp->next;
		}
	}
}

char	*join_after_expansion(t_list **splitted_token)
{
	t_list	*tmp;
	char	*save;
	char	*new;

	tmp = *splitted_token;
	new = ft_strdup("\0");
	while (tmp)
	{
		save = ft_strdup(new);
		free(new);
		new = NULL;
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
