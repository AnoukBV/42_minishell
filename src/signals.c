/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:31:05 by abernade          #+#    #+#             */
/*   Updated: 2024/04/24 11:41:05 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	shell_signals_handler(int sig)
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
	}
}

void	set_rl_signals(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	if (sigaddset(&sa.sa_mask, SIGQUIT) == -1 \
		|| sigaddset(&sa.sa_mask, SIGINT) == -1)
	{
		strerror(errno);
		exit(errno);
	}
	sa.sa_handler = &shell_signals_handler;
	if(sigaction(SIGQUIT, &sa, NULL) == -1 \
		|| sigaction(SIGINT, &sa, NULL) == -1)
	{
		strerror(errno);
		exit(errno);
	}
}
