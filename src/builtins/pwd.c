/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:14:59 by abernade          #+#    #+#             */
/*   Updated: 2024/05/15 12:44:01 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_pwd(void)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, PATH_MAX) == NULL)
	{
		perror("minishell: pwd: ");
		return (1);
	}
	ft_printf("%s\n", buf);
	return (0);
}
