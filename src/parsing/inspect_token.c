/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspect_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:05:16 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/27 17:33:52 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	isolate_not_exp(int save, int i, char *str, t_list **split)
{
	t_list	*new;
	char	*add;

	new = NULL;
	if (i - save < 1)
		return ;
	add = ft_substr(str, save, i - save);
	new = ft_lstnew(add);
	ft_lstadd_back(split, new);
}

static int	isolate_exp(char *str, t_list **env, t_list **split, t_esc *stat)
{
	char	*add;
	int		i;

	i = 1;
	if (!str[i] || (str[0] == '$' && str[i] == '\'' && stat->is_quoted == true) \
		|| (ft_isspace(str[i]) || (is_char_exp(str[i], 1) == false \
		&& (str[i] != '?' && ((str[i] != '"' && str[i] != '\'') \
		|| (stat->is_quoted == true && str[i] == '"'))))))
	{
		ft_lstadd_back(split, ft_lstnew(ft_strdup("$")));
		return (i);
	}
	while (str[i] && (is_char_exp(str[i], i) == true || str[i] == '?'))
	{
		check_quote(stat, &str[i]);
		i++;
	}
	add = expand(str, env, i);
	if (add)
		ft_lstadd_back(split, ft_lstnew(add));
	if (str[1] == '?')
		i = 2;
	return (i);
}

char	*inspect_token(char *str, t_list **env)
{
	int		i;
	int		begin;
	t_list	*split;
	t_esc	stat;

	i = 0;
	split = NULL;
	stat.is_quoted = false;
	begin = i;
	while ((size_t)i < ft_strlen(str) || str[i])
	{
		check_quote(&stat, &str[i]);
		if ((str[i] == '$' && stat.is_quoted == false) || (str[i] == '$' && \
			stat.is_quoted == true && stat.is_simplequote == false))
		{
			isolate_not_exp(begin, i, str, &split);
			i += isolate_exp(&str[i], env, &split, &stat);
			begin = i;
		}
		else
			i++;
	}
	if (begin != (int)ft_strlen(str))
		isolate_not_exp(begin, i, str, &split);
	return (join_after_expansion(&split));
}
