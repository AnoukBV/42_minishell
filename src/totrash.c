/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   totrash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:54:38 by aboulore          #+#    #+#             */
/*   Updated: 2024/04/30 19:21:27 by aboulore         ###   ########.fr       */
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
		printf("type = %i\n", redir->type);
		redir = redir->next;
	}
}

void	print_divided_cmds(t_btree *cmds, size_t levels)
{
	size_t	i;
	t_pcmd	*cmd;

	i = 0;
	if (!cmds)
		return ;
	cmd = (t_pcmd *)cmds->item;
	while (i < levels)
	{
		if (i == levels - 1)
			printf("|-");
		else
			printf(" ");
		i++;
	}
	printf("\nNODE NB %zu\n", levels);
	printf("\ntype = %i", cmd->flags);
	if (cmd->cmd)
	{
		printf("\ncmd + arg = \n");
		print_unidentified_tokens(cmd->cmd);
	}
	if (cmd->redir_list)
	{
		printf("\nRedirections\n");
		print_redirections((t_redir_list *)cmd->redir_list);
	}
	print_divided_cmds(cmds->left, levels + 1);
	print_divided_cmds(cmds->right, levels + 1);
}
