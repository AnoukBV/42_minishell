/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:25:47 by abernade          #+#    #+#             */
/*   Updated: 2024/06/06 13:12:28 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern int	g_status;

void	rl_signals_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \b\b", 1);
		return ;
	}
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = sig;
	}
}

void	exec_sig_handler(int sig)
{
	if (sig == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)", 2);
	ft_putchar_fd('\n', 1);
}

void	heredoc_sig_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \b\b", 1);
		return ;
	}
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		exit(128 + sig);
	}
}

void	empty_handler(int sig)
{
	(void)sig;
}
