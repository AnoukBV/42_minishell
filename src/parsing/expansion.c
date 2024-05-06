/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:23:07 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/06 17:55:33 by aboulore         ###   ########.fr       */
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

static char *expand(char *str, t_hashtable **env, t_esc *esc_status)
{
	char	*exp;
	char	*key;
	t_esc	save;
	size_t	i;

	i = 1;
	if (ft_strchr(str, '\"') && str[-1])
		check_quote(esc_status, &str[-1]);
	while (str[i] != '$' && str[i])
	{
		save = *esc_status;
	  	if (str[i + 1])
			check_quote(esc_status, &str[i + 1]);
		//if (str[i] != '\'' && str[i] != '"' && esc_status.is_quoted == true)
		if (save.is_quoted == true && esc_status->is_quoted == false)
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

static t_bool	check_expansion(t_exp **expansion, char *str)
{
	t_exp	*exp_status;

	exp_status = *expansion;
	check_quote(exp_status->esc_status, str);
	if ((exp_status->esc_status->is_quoted == true && exp_status->esc_status->is_simplequote \
			== false && str[0] == '$') || (exp_status->esc_status->is_quoted == false \
			&& str[0] == '$'))
		exp_status->is_exp = true;
	if (exp_status->is_exp == true && str[0] == '\"' && exp_status->esc_status->is_quoted == true)
		exp_status->is_exp = false;
	return (exp_status->is_exp);
}

static void	init_tracker(t_exp **exp_status)
{
	*exp_status = malloc(sizeof(t_exp));
	if (!(*exp_status))
		return ;
	(*exp_status)->esc_status = malloc(sizeof(t_esc));
	if (!(*exp_status)->esc_status)
		return ;
	(*exp_status)->esc_status->is_quoted = false;
	(*exp_status)->is_exp = false;
}

static void	inspect_token(char **str, t_hashtable **env)
{
	size_t	i;
	size_t	j;
	t_list	*splitted_token;
	t_list	*new;
	//char *tmp;
	t_exp	*exp_status;

	i = 0;
	splitted_token = NULL;
	init_tracker(&exp_status);
	while (str[0][i])
	{
		j = i;
		while (str[0][i] && check_expansion(&exp_status, &str[0][i]) == false)
			i++;
		if (j != i)
		{
			new = ft_lstnew(ft_substr(str[0], j, i));
			ft_lstadd_back(&splitted_token, new);
		}
		j = i;
		while (str[0][i] && check_expansion(&exp_status, &str[0][i]) == true)
		{
			i++;
			if (str[0][i] == '$' /*&& check_expansion(&exp_status, &str[0][i]) == false*/)
				break ;
		}
		if (j != i)
		{
			new = ft_lstnew(expand(&str[0][j], env, exp_status->esc_status));
			ft_lstadd_back(&splitted_token, new);
		}
		//i++;
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
