/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:48:23 by aboulore          #+#    #+#             */
/*   Updated: 2024/04/29 02:56:41 by abernade         ###   ########.fr       */
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

void	open_error(t_pipeline *pipeline)
{
	perror("open error: ");
	(void)pipeline;
	//destroy_pipeline(pipeline);
	exit(errno);
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