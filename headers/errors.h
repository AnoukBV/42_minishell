/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:24:02 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/26 13:04:15 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "minishell.h"

void	generic_error(t_pipeline *pipeline);
void	simple_generic_error(char *str);
void	malloc_error(void);
void	open_error(char *filename, t_pipeline *pipeline);
void	check_execve_error(char *pathname, t_pipeline *pipeline);
void	command_not_found_error(char *name, t_pipeline *pipeline);
void	heredoc_eof_warning(const char *delimiter);

#endif