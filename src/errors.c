/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:48:23 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/15 16:28:39 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_error(void)
{
	printf("tkt error\n");
}

void	redirection_error(t_command *cmd_lst)
{
	perror(NULL);
	(void)cmd_lst;
	//close_pipeline(cmd_lst);
}

void	pipe_error(t_pipeline *pipeline)
{
	(void)pipeline;
	perror(NULL);
	//free_cmd_list(pipeline->cmd_list);
	exit(errno);
}

void	malloc_error(void)
{
	perror(NULL);
	exit(errno);
}
void	dup2_error(void)
{
	perror(NULL);
	exit(errno);
}

void	open_error(char *filename)
{
	char	*errstr;

	errstr = ft_strjoin("minishell: ", filename);
	perror(errstr);
	free(errstr);
	exit(1);
}

void	fork_error(t_pipeline *pipeline)
{
	(void)pipeline;
	/*
	*	todo
	*/
}

void	check_execve_error(char *pathname, t_pipeline *pipeline)
{
	char	*errstr;
	int		exit;

	exit = 0;
	if (access(pathname, F_OK))
		exit = 127;
	else if (access(pathname, X_OK))
		exit = 126;
	if (!exit)
		return ;
	errstr = ft_strjoin("minishell: ", pathname);
	perror(errstr);
	free(errstr);
	destroy_pipeline(pipeline);
}

void	command_not_found_error(char *name)
{
	char *errstr;

	errstr = ft_strjoin(name, ": command not found\n");
	ft_putstr_fd(errstr, 2);
	free(errstr);
	exit(127);
}
