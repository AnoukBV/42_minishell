/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 07:59:46 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/02 11:04:41 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	undefault_fd_tree(int tok_flags, int *open_flags, int *fd)
{
	*fd = tok_flags / 1000;
	if (tok_flags % 1000 == T_APP_OUT)
		*open_flags = O_APPEND;
	else if (tok_flags % 1000 == T_RED_OUT || tok_flags % 1000 == T_RED_IN)
		*open_flags = O_TRUNCATE;
	else if (tok_flags % 1000 == T_APP_IN)
		*open_flags = O_HEREDOC;
}

void	assignate_flags_dir(int tok_flags, int *open_flags, int *fd)
{
	if (tok_flags < 1000)
	{
		if (tok_flags == T_RED_OUT)
		{
			*open_flags = O_TRUNCATE;
			*fd = 1;
		}
		else if (tok_flags == T_RED_IN)
		{
			*open_flags = O_TRUNCATE;
			*fd = 0;
		}
		else if (tok_flags == T_APP_IN)
		{
			*open_flags = O_HEREDOC;
			*fd = 0;
		}
		else if (tok_flags == T_APP_OUT)
		{
			*open_flags = O_APPEND;
			*fd = 1;
		}
	}
	else if (tok_flags >= 1000)
		undefault_fd_tree(tok_flags, open_flags, fd);
}

static int	ft_isanumber(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	undefault_fd_tok(t_list **list, t_wd_desc **redir)
{
	t_list		*curr;
	t_list		*prev;
	t_wd_desc	*tok;
	t_wd_desc	*fd;

	curr = *list;
	while (curr && curr->next)
	{
		tok = (t_wd_desc *)curr->next->content;
		if (tok == (*redir))
			break ;
		prev = curr;
		curr = curr->next;
	}
	fd = (t_wd_desc *)curr->content;
	if (!ft_isanumber(fd->word) || fd->flags != 0)
	{
		(*redir)->flags = 0;
		return ;
	}
	(*redir)->flags = ft_atoi(fd->word) * 1000;
	if (curr == *list)
		*list = curr->next;
	else if (curr->next && prev)
		prev->next = curr->next;
	ft_lstdelone(curr, &del_wddesc);
}
