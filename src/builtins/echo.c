/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:43:30 by abernade          #+#    #+#             */
/*   Updated: 2024/05/15 13:48:21 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_echo(char **argv)
{
	char	flag_n;
	int		i;

	i = 1;
	flag_n = (!ft_strncmp(argv[1], "-n", 3));
	if (flag_n)
		i++;
	while (argv[i])
	{
		if (i > 2 || (i == 2 && !flag_n))
			ft_putchar_fd(" ", 1);
		ft_printf("%s", argv[i]);
		i++;
	}
	if (flag_n)
		ft_putchar_fd("\n", 1);
	return (0);
}
