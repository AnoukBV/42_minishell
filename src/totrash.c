/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   totrash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:54:38 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/08 19:10:12 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_2d_array(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
	  	if (i == 0)
			ft_putstr_fd("command: ", 1);
		else
		{
			ft_putstr_fd("arg ", 1);
			ft_putnbr_fd(i, 1);
			ft_putstr_fd(":", 1);
		}
		ft_putstr(str[i]);
		ft_putstr("\n");
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
	if (cmd->argv)
		print_tokens((t_list *)cmd->argv);
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

void	print_divided_cmds_array(t_btree *cmds, size_t levels)
{
	t_command	*cmd;

	if (!cmds)
		return ;
	print_divided_cmds_array(cmds->right, levels + 1);
	for (size_t i = 0; i < levels; ++i)
		printf("     ");
	cmd = (t_command *)cmds->item;
	if (cmd->argv)
		print_2d_array((char **)cmd->argv);
	else
		printf(" %i ", cmd->flags);
	if (cmd->redir_list)
	{
		printf("\nRedirections\n");
		print_redirections((t_redir_list *)cmd->redir_list);
	}
	printf("\n");
	print_divided_cmds_array(cmds->left, levels + 1);
}

void	print_commands(t_command *list)
{
	size_t	i = 0;
	t_command *cmd = list;

	while (cmd)
	{
	  	printf("\ncmd num %zu\n", i);
	  	printf("\nis_argv = %d\n", cmd->is_argv);
		if (cmd->argv && cmd->is_argv == true)
			print_2d_array(cmd->argv);
		//else if c une autre t_command recur
		printf("\nflag = %i\n", cmd->flags);
		if (cmd->redir_list)
		{
			printf("\nRedirections\n");
			print_redirections((t_redir_list *)cmd->redir_list);
		}
		printf("\n");
		cmd = cmd->next;
		i++;
	}

}

void	print_pipeline(t_pipeline *pipeline)
{
	printf("\n\n----PIPELINE AFTER PARSING----\n\n");
	printf("\nno fd or pid list for now\n");
	printf("\n\nEnv for this pipeline (in a t_hashtable):\n\n");
	print_env(pipeline->envp, ENV),
	printf("\n\nList of ordered commands:\n-flags: to know which fd to redirect, or if you should check the exit code etc, the flag matches the control operator AFTER the cmd. ex: ls -l | wc -l --> flag for ls -l is T_PIPE(3), for wc -l is EMPTY(0)\n-is_arg: to know if argv points to another command (false) or a char ** (true)\n\n");
	print_commands(pipeline->cmd_list);
}
