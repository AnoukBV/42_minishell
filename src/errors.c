/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:48:23 by aboulore          #+#    #+#             */
/*   Updated: 2024/04/30 17:12:05 by abernade         ###   ########.fr       */
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

void	execve_error(void)
{
	perror(NULL);
	exit(errno);
}