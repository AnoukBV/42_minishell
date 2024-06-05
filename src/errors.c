/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:48:23 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/05 12:13:45 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	malloc_error(void)
{
	perror(NULL);
	exit(1);
}

void	dup2_error(void)
{
	perror(NULL);
	exit(1);
}

void	fork_error(t_pipeline *pipeline)
{
	(void)pipeline;
	/*
	*	todo
	*/
}


void	heredoc_eof_warning(const char *delimiter)
{
	ft_putstr_fd("minishell: here-document delimited by end-of-file,\
		 (wanted ", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd(")\n", 2);
}
