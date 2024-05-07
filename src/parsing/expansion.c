/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:23:07 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/07 14:07:37 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static void	inspect_redir(t_redir_list **redir_list)
{
	filename et limiter
}
*/
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
//	if (cmd->redir_list)
//		inspect_redir(&cmd->redir_list);
//	MAINTENANT REMOVE QUOTES QUI RESTENT
}
