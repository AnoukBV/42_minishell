/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:23:07 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/31 12:33:54 by aboulore         ###   ########.fr       */
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
	char		*save2;

	save = inspect_token(token, env);
	//free(save);
	save2 = ft_strtrim(save, " \t");
	free(save);
	return (save2);
}

void	expansion(t_list **inputs, t_list *env)
{
	char	*res;
	t_list		*tmp;
	t_wd_desc	*token;
	//char	*final;

	tmp = *inputs;
	//while (tmp)
	//{
	
	while (tmp)
	{
		token = (t_wd_desc *)tmp->content;
		if (ft_strchr(token->word, '$'))
		{
			//printf("\n[expansion] token BEFORE expansion_inspection: %s\n", token->word);
			res = token->word;
			token->word = expansion_inspection(token->word, &env);
			//printf("\n[expansion] token AFTER expansion: %s\n", token->word);

			free(res);
			
		}
		tmp = tmp->next;
	}
	
}
