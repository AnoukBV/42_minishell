/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:48:23 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/30 17:15:58 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>



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

void	fork_error(t_pipeline *pipeline)
{
	(void)pipeline;
	/*
	*	todo
	*/
}
