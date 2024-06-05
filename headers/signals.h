/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:26:57 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/05 11:08:59 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

void	set_rl_signals(void);
void	set_heredoc_signals(void);
void	signals_default(void);
void	set_exec_signals(void);
void	rl_signals_handler(int sig);
void	exec_sig_handler(int sig);
void	heredoc_sig_handler(int sig);
void	empty_handler(int sig);

#endif