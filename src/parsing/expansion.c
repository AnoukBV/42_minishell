/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:23:07 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/07 15:47:51 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	inspect_redir(t_redir_list **redir_list, t_hashtable **env)
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
}
void	inspect_cmd(t_list **cmd, t_hashtable **env)
{
	t_list		*tmp;
	t_wd_desc	*tok;

	tmp = *cmd;
	while (tmp)
	{
		tok = (t_wd_desc *)tmp->content;
		if (ft_strchr(tok->word, '$'))
			inspect_token(&tok->word, env);
		tmp = tmp->next;
	}
}
void	expansion(void *item)
{
	t_command	*cmd;

	cmd = (t_command *)item;
	if (cmd->cmd)
		inspect_cmd(&cmd->cmd, cmd->env);
	if (cmd->redir_list)
		inspect_redir(&cmd->redir_list, cmd->env);
}
/*
void	remove_quotes(void *item)
{
	t_command	*cmd;

	cmd = (t_command *)item;

}*/
