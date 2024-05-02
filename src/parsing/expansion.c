/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:23:07 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/02 16:56:31 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*inspect_token(void *item)
{
	size_t	i;
	t_wd_desc	*tok;
	t_esc	esc_status;

	i = 0;
	tok = (t_wd_desc *)item;
	if (!ft_strchr(tok->word, '$'))
	{		
		printf("nothin to expand: %s\n", tok->word);
		return (tok);
	}
	esc_status.is_quoted = false;
	while (tok->word[i])
	{
		check_quote_bis(&esc_status, &tok->word[i]);
		if ((esc_status.is_quoted == true && esc_status.is_simplequote \
			== false && tok->word[i] == '$') || (esc_status.is_quoted == false \
			&& tok->word[i] == '$'))
				printf("expand : %s\n", &tok->word[i]);
				//expand(tok->word);
		i++;
	}
	return (new_wd_desc(tok->flags, ft_strdup(tok->word)));
}

/*
static void	inspect_redir(t_redir_list **redir_list)
{
}
*/
void	inspect_cmd(t_list **cmd, t_hashtable **env)
{
	t_list	*new;
	t_list	*save;

	save = *cmd;
	new = ft_lstmap(*cmd, &inspect_token, &del_wddesc);
	ft_lstclear(&save, del_wddesc);
	*cmd = new;
}
void	expansion(void *item)
{
	t_command	*cmd;

	cmd = (t_command *)item;
	if (cmd->cmd)
		inspect_cmd(&cmd->cmd, cmd->env);
//	if (cmd->redir_list)
//		inspect_redir(&cmd->redir_list);
}
