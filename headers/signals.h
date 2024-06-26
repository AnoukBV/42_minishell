/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:26:57 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/06 09:11:18 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

void	set_rl_signals(void);
void	set_heredoc_signals(void);
void	disable_signals(void);
void	set_exec_signals(void);

// handlers
void	rl_signals_handler(int sig);
void	exec_sig_handler(int sig);
void	heredoc_sig_handler(int sig);
void	empty_handler(int sig);

#endif