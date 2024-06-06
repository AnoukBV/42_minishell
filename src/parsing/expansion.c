/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:23:07 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/06 11:02:32 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expansion_inspection(char *token, t_list **env, \
	int flag, t_list **inputs)
{
	char		*save;
	int			new_flag;
	char		*save2;

	if (flag != T_RED_IN && flag != T_RED_OUT \
		&& flag != T_APP_IN && flag != T_APP_OUT)
		new_flag = 0;
	else
		new_flag = 1;
	save = inspect_token(token, env);
	if (save == NULL && new_flag == 1)
		red_experr_prompt(token, inputs, env);
	if (!save)
		return (NULL);
	save2 = ft_strtrim(save, " \t");
	free(save);
	return (save2);
}

static int	new_token_word(char **word, \
	t_wd_desc *prev, t_list **inputs, t_list **env)
{
	int		save;
	char	*res;

	save = prev->flags;
	res = expansion_inspection(*word, env, prev->flags, inputs);
	if (!res && (save <= T_RED_OUT || save >= T_APP_IN))
	{
		ft_lstclear(inputs, &del_wddesc);
		return (0);
	}
	else if (!res)
		return (1);
	free(*word);
	*word = res;
	return (0);
}

int	expansion(t_list **inputs, t_list *env)
{
	t_list		*tmp;
	t_wd_desc	*prev;
	t_wd_desc	*token;

	tmp = *inputs;
	prev = tmp->content;
	while (tmp)
	{
		token = (t_wd_desc *)tmp->content;
		if (ft_strchr(token->word, '$') && prev->flags != T_APP_IN)
		{
			if (new_token_word(&token->word, prev, inputs, &env) == 1)
				return (1);
		}
		else if (ft_strchr(token->word, '$') && prev->flags == T_APP_IN)
			heredoc_expansion(&token->word);
		if (!(*inputs))
			tmp = *inputs;
		if (tmp)
		{
			prev = tmp->content;
			tmp = tmp->next;
		}
	}
	return (0);
}

t_bool	is_char_exp(char c, int i)
{
	if (i == 1 && (!ft_isalpha(c) && c != '_'))
		return (false);
	if (!ft_isalnum(c) && c != '_')
		return (false);
	return (true);
}
