/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   totrash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:54:38 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/07 16:07:40 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_2d_array(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		ft_putstr("\nNEW_INPUT: ");
		ft_putstr(str[i]);
		i++;
	}
}

int Size(t_btree *root)
{
        if (root == NULL)
        {
            return 0;
        }

        return Size(root->left) + Size(root->right) + 1;
}

void	print_unidentified_tokens(t_list *inputs)
{
	size_t	j;
	size_t	size_input;
	t_list	*tmp;
	t_wd_desc	*word;

	tmp = inputs;
	printf("\nDATA\n");
	j = 0;
	size_input = ft_lstsize(tmp);
	while (j < size_input)
	{
		printf("\nTOKEN N°%zu\n", j);
		word = (t_wd_desc*)tmp->content;
		printf("flags = %i\n", word->flags);
		printf("value = %s\n", word->word);
		tmp = tmp->next;
		j++;
	}
	printf("\n");
}

void	print_redirections(t_redir_list *tmp)
{
	t_redir_list	*redir;

	redir = tmp;
	if (!redir)
		return ;
	while (redir)
	{
		printf("%s\n", redir->target_filename);
		printf("flags = %i\n", redir->open_flags);
		printf("fd = %i\n", redir->fd_to_redirect);
		redir = redir->next;
	}
}

void	print_tokens(t_list *inputs)
{
	size_t	j;
	size_t	size_input;
	t_list	*tmp;
	t_wd_desc	*word;

	tmp = inputs;
	j = 0;
	size_input = ft_lstsize(tmp);
	while (j < size_input)
	{
		word = (t_wd_desc*)tmp->content;
		printf("%s ", word->word);
		tmp = tmp->next;
		j++;
	}
	printf("STOP");
}

void	print_divided_cmds(t_btree *cmds, size_t levels)
{
	t_command	*cmd;

	if (!cmds)
		return ;
	print_divided_cmds(cmds->right, levels + 1);
	for (size_t i = 0; i < levels; ++i)
		printf("     ");
	cmd = (t_command *)cmds->item;
	if (cmd->cmd)
		print_tokens(cmd->cmd);
	else
		printf(" %i ", cmd->flags);
	if (cmd->redir_list)
	{
		printf("\nRedirections\n");
		print_redirections((t_redir_list *)cmd->redir_list);
	}
	printf("\n");
	print_divided_cmds(cmds->left, levels + 1);
}
