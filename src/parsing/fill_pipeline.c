/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:54:49 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/06 09:32:00 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_next_heredoc(char *name)
{
	char	*for_exp;
	char	*tmp;
	char	*save;
	int		fd;

	fd = open(name, O_RDONLY);
//	tmp = get_next_line(fd);
	for_exp = ft_strdup("");
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		save = for_exp;
		for_exp = ft_strjoin(save, tmp);
		free(save);
		free(tmp);
		
	}
	//free(save);
	free(tmp);
	close(fd);
	return (for_exp);
}

char	*fill_heredoc(int flag, t_list **env, char *delimiter, t_command **cmd)
{
	char	*name;
	char	*save;
	char	*for_exp;
	int		fd;

	name = new_heredoc(delimiter, env, cmd);
	if (name && flag == T_APP_IN)
	{
		for_exp = get_next_heredoc(name);
		if (ft_strchr(for_exp, '$'))
		{
			save = for_exp;
			for_exp = inspect_token(save, env);
			free(save);
			fd = open(name, O_RDWR, O_TRUNC);
			ft_putstr_fd(for_exp, fd);
			free(for_exp);
			close(fd);
		}
		else
			free(for_exp);
	}
	return (name);
}

int	heredoc_inspection(t_redir_list **redirs, t_list **env, t_command **cmd)
{
	t_redir_list	*tmp;
	char			*name;

	tmp = *redirs;
	while (tmp)
	{
		if (tmp->open_flags == T_APP_IN || tmp->open_flags == T_APP_IN + 100)
		{
			name = fill_heredoc(tmp->open_flags, env, tmp->target_filename, cmd);
			if (!name)
				return (-1);
			free(tmp->target_filename);
			tmp->target_filename = name;
			tmp->open_flags = O_RDONLY;
			tmp->heredoc = true;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	add_flags(t_command **cmd, t_list **env)
{
	t_command	*tmp;
	t_command	*save;

	tmp = *cmd;
	if (!tmp)
		return (0);
	save = tmp;
	while (tmp)
	{
		if (tmp->flags != T_WORD && tmp->flags != EMPTY)
		{
			save->flags = tmp->flags;
			save->next = tmp->next;
			save->next->prev = save;
			destroy_cmd_one(tmp, NULL);
			tmp = save;
		}
		if (tmp->redir_list)
			if (heredoc_inspection(&tmp->redir_list, env, cmd) == -1)
				return (-1);
		save = tmp;
		tmp = tmp->next;
	}
	return (0);
}

void	order_commands(t_command **cmd, t_btree *tree)
{
	if (!tree)
		return ;
	if (tree->left)
		order_commands(cmd, tree->left);
	command_addback(cmd, (t_command *)tree->item);
	if (tree->right)
		order_commands(cmd, tree->right);
}

int	fill_pipeline(t_pipeline **pipeline, t_btree *tree, t_list *env)
{
	t_command	*cmd_list;

	cmd_list = NULL;
	if (tree)
		order_commands(&cmd_list, tree);
	if (cmd_list)
	{
		if (add_flags(&cmd_list, &env) == -1)
		{
			destroy_cmd_list(&cmd_list, env);
			return (-1);
		}
	}
	*pipeline = init_pipeline(cmd_list, env);
	return (0);
}
