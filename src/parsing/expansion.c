/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:23:07 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/03 07:37:44 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	join_after_expansion(char **tok, t_list **splitted_token)
{
	t_list	*tmp;
	char	*save;
	char	*new;

	tmp = *splitted_token;
	new = "\0";
	while (tmp)
	{
		save = ft_strdup(new);
		new = ft_strjoin(save, (char *)tmp->content);
		free(save);
		tmp = tmp->next;
	}
	//ft_lstclear(splitted_token, &del_wddesc);
	*tok = new;
}

static char *seek_env(char *key, t_hashtable **env)
{
	t_member	**table;
	size_t	i;

	i = 0;
	table = (t_member **)(*env)->member;
	while (i < (*env)->size - 1)
	{
		if (table[i] && table[i]->key && \
			!ft_strncmp(table[i]->key, key, ft_strlen(key)))
			return (table[i]->value);
		i++;
	}
	return ("\0");
}

static char *expand(char *str, t_hashtable **env)
{
	char	*exp;
	char	*key;
	t_esc	esc_status;
	size_t	i;

	i = 1;
	while (str[i] != '$' && str[i])
	{
	  	if (str[i + 1])
			check_quote(&esc_status, &str[i + 1]);
		if (str[i] != '\'' && str[i] != '"' && esc_status.is_quoted == true)
			break ;
		i++;
	}
	if (i == 1)
		return ("$");
	key = ft_substr(str, 1, i - 1);
	exp = ft_strdup(seek_env(key, env));
	free(key);
	key = NULL;
	return (exp);
}

static void	*inspect_token(void *item, t_hashtable **env)
{
	size_t	i;
	t_list	*splitted_token;
	t_list	*new;
	t_wd_desc	*tok;
	t_esc	esc_status;

	i = 0;
	splitted_token = NULL;
	tok = (t_wd_desc *)item;
	if (!ft_strchr(tok->word, '$'))
		return (tok);
	esc_status.is_quoted = false;
	while (tok->word[i])
	{
		check_quote_bis(&esc_status, &tok->word[i]);
		if ((esc_status.is_quoted == true && esc_status.is_simplequote \
			== false && tok->word[i] == '$') || (esc_status.is_quoted == false \
			&& tok->word[i] == '$'))
		{
			new = ft_lstnew(expand(&tok->word[i], env));
			ft_lstadd_back(&splitted_token, new);
		}
		i++;
	}
	if (splitted_token)
		join_after_expansion(&tok->word, &splitted_token); //free tok_word la dedans
	//print_unidentified_tokens(splitted_token);
	printf("%s\n", tok->word);
	return (tok);
}

/*
static void	inspect_redir(t_redir_list **redir_list)
{
	filename et limiter
}
*/
void	inspect_cmd(t_list **cmd, t_hashtable **env)
{
	t_list	*tmp;

	tmp = *cmd;
	while (tmp)
	{
		tmp->content = inspect_token(tmp->content, env);
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
