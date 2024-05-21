/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:31:05 by abernade          #+#    #+#             */
/*   Updated: 2024/05/21 14:15:07 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_rl_signals(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	if (sigaddset(&sa.sa_mask, SIGQUIT) == -1 \
		|| sigaddset(&sa.sa_mask, SIGINT) == -1)
	{
		perror(NULL);
		exit(errno);
	}
	sa.sa_handler = &rl_signals_handler;
	if(sigaction(SIGQUIT, &sa, NULL) == -1 \
		|| sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror(NULL);
		exit(errno);
	}
}

void	set_exec_signals(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = &exec_sig_handler;
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sa, NULL) == -1 \
		|| sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror(NULL);
		exit(errno);
	}
}

/*
*	Currently unused
*/
void	signals_default(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	if (sigaction(SIGQUIT, &sa, NULL) == -1 \
		|| sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror(NULL);
		exit(errno);
	}
}
