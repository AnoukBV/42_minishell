/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dummydata.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:12:02 by abernade          #+#    #+#             */
/*   Updated: 2024/05/02 18:21:56 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	cmd_add_back(t_command **cmd_list, t_command *cmd)
{
	t_command	*node;	

	if (cmd_list == NULL)
		fprintf(stderr, "cmd_add_back: arrete de faire n'importe quoi\n");
	else if (*cmd_list == NULL)
		*cmd_list = cmd;
	else
	{
		node = *cmd_list;
		while (node->next != NULL)
			node = node->next;
		node->next = cmd;
		cmd->prev = node;
	}
}

static void	redir_add_back(t_redir_list **redir_list, t_redir_list *redir)
{
	t_redir_list *node;

	if (redir_list == NULL)
		fprintf(stderr, "redir_add_back: arrete de faire n'importe quoi\n");
	else if (*redir_list == NULL)
		*redir_list = redir;
	else
	{
		node = *redir_list;
		while (node->next != NULL)
			node = node->next;
		node->next = redir;
	}
}

t_pipeline	*dummydata(char **envp)
{
	t_pipeline		*pipeline;
	t_command		*cmd;
	t_redir_list	*redirs;

	pipeline = malloc(sizeof(t_pipeline));
	pipeline->envp = envp;
	pipeline->pid_list = NULL;
	pipeline->fd_list = NULL;
	pipeline->cmd_list = NULL;

	cmd = malloc(sizeof(t_command));
	cmd->command = ft_strdup("/usr/bin/cat");
	cmd->argv = malloc(sizeof(char*) * 2);
	cmd->argv[0] = ft_strdup("/usr/bin/cat");
	cmd->argv[1] = NULL;
	cmd->prev = NULL;	
	cmd->next = NULL;
	redirs = malloc(sizeof(t_redir_list));
	redirs->fd_to_redirect = 0;	
	redirs->open_flags = O_RDONLY;
	redirs->target_filename = ft_strdup("Makefile");
	redirs->next = NULL;
	cmd->redir_list = redirs;
	cmd_add_back(&pipeline->cmd_list, cmd);

	cmd = malloc(sizeof(t_command));
	cmd->command = ft_strdup("/usr/bin/grep");
	cmd->argv = malloc(sizeof(char*) * 3);
	cmd->argv[0] = ft_strdup("/usr/bin/grep");
	cmd->argv[1] = ft_strdup("src");
	cmd->argv[2] = NULL;
	cmd->prev = NULL;	
	cmd->next = NULL;
	redirs = malloc(sizeof(t_redir_list));
	redirs->fd_to_redirect = 1;	
	redirs->open_flags = O_WRONLY | O_TRUNC | O_CREAT;
	redirs->target_filename = ft_strdup("zoui");
	redirs->next = NULL;
	cmd->redir_list = redirs;
	redirs = malloc(sizeof(t_redir_list));
	redirs->fd_to_redirect = 1;	
	redirs->open_flags = O_WRONLY | O_TRUNC | O_CREAT;
	redirs->target_filename = ft_strdup("outfile");
	redirs->next = NULL;
	redir_add_back(&cmd->redir_list, redirs);
	cmd_add_back(&pipeline->cmd_list, cmd);

	cmd = malloc(sizeof(t_command));
	cmd->command = ft_strdup("test");
	cmd->argv = malloc(sizeof(char*) * 3);
	cmd->argv[0] = ft_strdup("test");
	cmd->argv[1] = ft_strdup("-l");
	cmd->argv[2] = NULL;
	cmd->prev = NULL;	
	cmd->next = NULL;
	redirs = malloc(sizeof(t_redir_list));
	redirs->fd_to_redirect = 0;	
	redirs->open_flags = O_RDONLY;
	redirs->target_filename = ft_strdup("outfile");
	redirs->next = NULL;
	cmd->redir_list = redirs;
	cmd_add_back(&pipeline->cmd_list, cmd);

	return (pipeline);
}
