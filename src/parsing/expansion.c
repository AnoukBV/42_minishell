/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:23:07 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/04 13:32:23 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;
/*
static void	inspect_redir(t_redir_list **redir_list, t_list **env)
{
	t_redir_list	*tmp;

	tmp = *redir_list;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (tmp->target_filename && ft_strchr(tmp->target_filename, '$'))
			inspect_token(&tmp->target_filename, env);
	//if (tmp->open_flags == O_HEREDOC)
	//faire un signe qui dise de ne pas expand les variables dans le hd
	//regarder ce qu'a fait arthur
		tmp = tmp->next;
	}
}*/

t_bool	is_char_exp(char c, int i)
{
	if (i == 1 && (!ft_isalpha(c) && c != '_'))
		return (false);
	if (!ft_isalnum(c) && c != '_')
		return (false);
	return (true);
}

char	*expansion_inspection(char *token, t_list **env, int flag, t_list **inputs)
{
	char		*save;
	int			new_flag;
	char		*save2;

	if (flag != T_RED_IN && flag != T_RED_OUT \
		&& flag != T_APP_IN && flag != T_APP_OUT)
		new_flag = 0;
	else
		new_flag = 1;
	save = inspect_token(token, env, new_flag, inputs);
	if (!save)
		return (NULL);
	//free(save);
	save2 = ft_strtrim(save, " \t");
	free(save);
	return (save2);
}

int	expansion(t_list **inputs, t_list *env)
{
	char	*res;
	int		save;
	t_list		*tmp;
	t_wd_desc	*prev;
	t_wd_desc	*token;

	tmp = *inputs;
	prev = tmp->content;
	while (tmp)
	{
		token = (t_wd_desc *)tmp->content;
		if (ft_strchr(token->word, '$'))
		{
			//printf("\n[expansion] token BEFORE expansion_inspection: %s\n", token->word);
		//	res = token->word;
			save = prev->flags;
			res = expansion_inspection(token->word, &env, prev->flags, inputs);
			if (!res && (save <= T_RED_OUT || save >= T_APP_IN))
			{
				ft_lstclear(inputs, &del_wddesc);
				//free(res);
				return (0);
			}
			else if (!res)
				return (1);
			free(token->word);
			token->word = res;
			
		}
		prev = tmp->content;
		tmp = tmp->next;
	}
	return (0);
}
