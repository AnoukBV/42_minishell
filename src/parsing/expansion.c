/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:23:07 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/29 11:11:35 by aboulore         ###   ########.fr       */
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

char	*expansion_inspection(char *token, t_list **env)
{
	char		*save;

	if (token[1] == '?')
		return (ft_itoa(g_status));
	else
		save = inspect_token(token, env);
	//free(save);
	return (save);
}

char	*expansion(char *word, t_list *env)
{
	//t_wd_desc	*token;
	//t_list		*tmp;
	char	*final;

	//tmp = *tokens;
	//while (tmp)
	//{
	//	token = (t_wd_desc *)tmp->content;
	if (ft_strchr(word, '$'))
	{
//			printf("\nIn expansion, token BEFORE expansion_inspection: %s\n", token->word);
		final = expansion_inspection(word, &env);
//		printf("\nIn expansion, token AFTER expansion: %s\n", token->word);
		return (final);
	}
	return (ft_strdup(word));
	//	tmp = tmp->next;
	
}
