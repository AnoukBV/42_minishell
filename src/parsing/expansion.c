/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:23:07 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/28 16:31:20 by aboulore         ###   ########.fr       */
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

void	expansion_inspection(char **token, t_list **env)
{
	char		*save;

	save = *token;
	if (token[0][1] == '?')
		token[0] = ft_itoa(g_status);
	else
		inspect_token(&token[0], env);
	free(save);
}

void	expansion(t_list **tokens, t_list *env)
{
	t_wd_desc	*token;
	t_list		*tmp;

	tmp = *tokens;
	while (tmp)
	{
		token = (t_wd_desc *)tmp->content;
		if (token->flags == 0 && ft_strchr(token->word, '$'))
		{
			printf("\nIn expansion, token BEFORE expansion_inspection: %s\n", token->word);
			expansion_inspection(&token->word, &env);
			printf("\nIn expansion, token AFTER expansion: %s\n", token->word);
		}
		tmp = tmp->next;
	}
}
