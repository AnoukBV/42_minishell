/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:23:07 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/07 12:53:40 by aboulore         ###   ########.fr       */
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

static char *expand(char *str, t_hashtable **env, size_t size)
{
	char	**exp;
	char	**to_exp;
	char	*key;
	char	*new;
	size_t	i;
	//size_t	j;

	i = 0;
	key = NULL;
	new = ft_substr(str, 0, size - 1);
	if (str[0] == '\"')
	{	
		to_exp = ft_split(new, '\"');
		free(new);
		new = NULL;
		//key = ft_superjoin(to_exp, NULL);
		key = ft_strdup(to_exp[0]);
		free_array_2d(to_exp);
		to_exp = NULL;
		new = key;
	}
	//key = ft_substr(str, i, j - 1);
	to_exp = ft_split(new, '$');
	if (key)
	{
		free(key);
		key = NULL;
	}
	i = 0;
	exp = ft_calloc(sizeof(char *), ft_arrlen(to_exp) + 1);
	if (!exp)
		return (NULL);
	while (to_exp[i])
	{
		exp[i] = ft_strdup(seek_env(to_exp[i], env));
		i++;
	}
	free_array_2d(to_exp);
	key = ft_superjoin(exp, NULL);
	free_array_2d(exp);
	return (key);
}

static t_bool	exp_between_quotes(char *str)
{
	size_t	i;
	char	*block;

	i = 1;
	block = ft_strchr(&str[i], '\"');
	while (&str[i] != block && str[i])
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

static t_bool	check_expansion(t_exp **expansion, char *str)
{
	static t_bool	save_q;
	t_exp	*exp_status;

	exp_status = *expansion;
	save_q = exp_status->esc_status->is_quoted;
	check_quote(exp_status->esc_status, str);

	if (exp_status->is_exp_sim == false && exp_status->is_exp_quo == false)
	{
		if (str[0] == '\"' && exp_status->esc_status->is_quoted == true && save_q == false \
			&& exp_between_quotes(str) == true)
		{
			exp_status->is_exp_quo = true;
			return (true);
		}
		else if (str[0] == '$')
		{
			exp_status->is_exp_sim = true;
			return (true);
		}
	}
	else if (exp_status->is_exp_sim == true)
	{
		if (ft_strchr("\'\"", str[1]) && str[2] && ft_strchr(&str[2], str[1]))
			exp_status->is_exp_sim = false;
		return (exp_status->is_exp_sim);
	}
	else if (exp_status->is_exp_quo == true)
	{
		if (str[0] == '\"' && exp_status->esc_status->is_quoted == false)	
			exp_status->is_exp_quo = false;
		return (exp_status->is_exp_quo);
	}
	return (false);
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
	(*exp_status)->is_exp_sim = false;
	(*exp_status)->is_exp_quo = false;
}

static void	inspect_token(char **str, t_hashtable **env)
{
	size_t	i;
	size_t	j;
	t_list	*splitted_token;
	t_list	*new;
	t_bool	exp;
	//char *tmp;
	t_exp	*exp_status;

	i = 0;
	j = i;
	splitted_token = NULL;
	init_tracker(&exp_status);
	while (str[0][i])
	{
		exp = check_expansion(&exp_status, &str[0][i]); 
		if (exp == false)
		{
			j = i;
			while (str[0][i] && exp == false && str[0][i] != '$')
			{
				i++;
				exp = check_expansion(&exp_status, &str[0][i]); 
			}
			if (j != i)
			{
				new = ft_lstnew(ft_substr(str[0], j, i - j));
				ft_lstadd_back(&splitted_token, new);
			}
		//	j = i;
		//	i++;
		}
		else
		{
			//j = i;
			while (str[0][i] && exp == true)
			{
				i++;
				exp = check_expansion(&exp_status, &str[0][i]); 
			}
			if (j != i)
			{
				new = ft_lstnew(expand(&str[0][j], env, i - j + 2));
				ft_lstadd_back(&splitted_token, new);
			}
		}
		j = i;
		i++;
	}
	if (splitted_token)
		join_after_expansion(&str[0], &splitted_token); //free tok_word la dedans
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
