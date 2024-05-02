/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:56:50 by abernade          #+#    #+#             */
/*   Updated: 2024/05/02 17:38:34 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_status(int status)
{
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	fprintf(stderr, "get_status error\n");
	return (-1);
}

t_bool	is_builtin(char *cmd_name)
{
	return (!ft_strncmp(cmd_name, "echo", 5) \
		|| !ft_strncmp(cmd_name, "cd", 3) \
		|| !ft_strncmp(cmd_name, "pwd", 4) \
		|| !ft_strncmp(cmd_name, "export", 7) \
		|| !ft_strncmp(cmd_name, "unset", 6) \
		|| !ft_strncmp(cmd_name, "env", 4) \
		|| !ft_strncmp(cmd_name, "exit", 5));
}
