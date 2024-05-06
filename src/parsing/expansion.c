/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:23:07 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/06 14:05:20 by aboulore         ###   ########.fr       */
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

static char *expand(char *str, t_hashtable **env, t_esc esc_status)
{
	char	*exp;
	char	*key;
	t_esc	save;
	size_t	i;

	i = 1;
	while (str[i] != '$' && str[i])
	{
		save = esc_status;
	  	if (str[i + 1])
			check_quote(&esc_status, &str[i + 1]);
		if (save.is_quoted == true && esc_status.is_quoted == false)
			break ;
		//if (str[i] != '\'' && str[i] != '"' && esc_status.is_quoted == true)
		//	break ;
		i++;
	}
	if (str[i] == '$' && str[i + 1] && str[i + 1] == '$')
		return ("$");
	key = ft_substr(str, 1, i - 1);
	exp = ft_strdup(seek_env(key, env));
	free(key);
	key = NULL;
	return (exp);
}

static void	inspect_token(char **str, t_hashtable **env)
{
	size_t	i;
	size_t	j;
	t_list	*splitted_token;
	t_list	*new;
	char *tmp;
	t_esc	esc_status;

	i = 0;
	j = 0;
	splitted_token = NULL;
	esc_status.is_quoted = false;
	while (str[0][i])
	{
		tmp = ft_strchr(&str[0][i], '$');
		if (tmp == NULL)
			break ;
		check_quote(&esc_status, &str[0][i]);
		while (tmp && &str[0][i] != tmp)
		{
			i++;
			check_quote(&esc_status, &str[0][i]);
		}
		j = i;
		if (&str[0][j] != tmp)
		{
			if (str[0][i - 1] && (str[0][i - 1] == '\'' || str[0][i - 1] == '"'))
			{
				new = ft_lstnew(ft_substr(str[0], j, i - 2));
				ft_lstadd_back(&splitted_token, new);
			}
			else if (str[0][i - 1])
			{
				new = ft_lstnew(ft_substr(str[0], j, i - 1));
				ft_lstadd_back(&splitted_token, new);
			}
		}
		//if (tmp && str[0][i - 1] && (str[0][i - 1] == '\'' || str[0][i - 1] == '\"'))
		//	i -= 1;
		if ((esc_status.is_quoted == true && esc_status.is_simplequote \
			== false && tmp) || (esc_status.is_quoted == false \
			&& tmp))
		{
			new = ft_lstnew(expand(&str[0][i], env, esc_status));
			ft_lstadd_back(&splitted_token, new);
		}	
		i++;
	}
	if (splitted_token)
		join_after_expansion(&str[0], &splitted_token); //free tok_word la dedans
	//print_unidentified_tokens(splitted_token);
	printf("%s\n", *str);
}

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
