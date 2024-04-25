/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:48:23 by aboulore          #+#    #+#             */
/*   Updated: 2024/04/25 19:19:29 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_error(void)
{
	printf("tkt error\n");
}

void	redirection_error(t_command *cmd_lst)
{
	perror(errno);
	close_pipeline(cmd_lst);
}

void	pipe_error(t_pipeline *pipeline)
{
	perror(errno);
	free_cmd_list(pipeline->cmd_list);
	exit(errno);
}

void	malloc_error()
{
	perror(errno);
	exit(errno);
}
void	dup2_error()
{
	perror(errno);
	exit(errno);
}

void	open_error(t_pipeline *pipeline)
{
	perror(errno);
	destroy_pipeline(pipeline);
	exit(errno);
}