/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:07:52 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/05 12:21:35 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*nothing_to_keep(t_wd_desc **res, \
	t_list **curr, t_list **tmp, t_list **prev)
{
	*res = (*tmp)->content;
	*curr = (*tmp)->next;
	(*prev)->next = *curr;
	free(*res);
	free(*tmp);
	//printf("\n[space_knitting] size of split when node to be deleted: %zu\n", ft_arrlen(split));
	return (*prev);
}

static t_list	*space_knitting(char **split, t_list **curr, t_list **prev)
{
	size_t		i;
	t_list		*tmp;
	t_wd_desc	*res;
	t_list		*new;

	i = 1;
	tmp = *curr;
	if (!split[0])
		return (nothing_to_keep(&res, curr, &tmp, prev));
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
	t_list		*tmp;
	t_list		*prev;
	t_wd_desc	*tok;

	tmp = *inputs;
	while (tmp)
	{
		tok = (t_wd_desc *)tmp->content;
		if (tok->flags == T_WORD)
			tmp = space_break(&tmp, &prev, tok->word);
		if (tmp)
		{
			prev = tmp;
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
		new = ft_strjoin(save, (char *)tmp->content);
		free(save);
		tmp = tmp->next;
	}
	ft_lstclear(splitted_token, free);
	save = ft_strtrim(new, " \t");
	free(new);
	new = save;
	if (*new == '\0')
	{
		free(new);
		new = NULL;
	}
	return (new);
}
