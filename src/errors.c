/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:48:23 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/16 16:28:48 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
