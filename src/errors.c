/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:48:23 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/06 09:02:02 by abernade         ###   ########.fr       */
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

void	simple_generic_error(void)
{
	perror(NULL);
	exit(1);
}

void	heredoc_eof_warning(const char *delimiter)
{
	ft_putstr_fd("minishell: here-document delimited by end-of-file", 2);
	ft_putstr_fd(", (wanted '", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);

}
