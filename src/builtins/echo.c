/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:43:30 by abernade          #+#    #+#             */
/*   Updated: 2024/05/30 16:44:13 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define FLAG_N 1

static t_bool	echo_is_flag(char *str)
{
	if (*str != '-')
		return (false);
	str++;
	while (*str)
	{
		if (*str != 'n')
			return (false);
		str++;
	}
	return (true);
}

static void	echo_add_flags(int *flags, char *str)
{
	str++;
	while (*str)
	{
		if (*str == 'n')
			*flags |= FLAG_N;
		str++;
	}
}

static int	echo_handle_flags(int *flags, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (echo_is_flag(argv[i]))
		{
			echo_add_flags(flags, argv[i]);
			i++;
		}
		else
			return (i);
	}
	return (i);
}

int	builtin_echo(char **argv)
{
	t_bool	first;
	int		flags;
	int		i;

	first = true;
	flags = 0;
	i = echo_handle_flags(&flags, argv);
	while (argv[i])
	{
		if (!first)
			ft_putchar_fd(' ', 1);
		else
			first = false;
		ft_putstr_fd(argv[i], 1);
		i++;
	}
	if (!(flags & FLAG_N))
		ft_putchar_fd('\n', 1);
	return (0);
}
