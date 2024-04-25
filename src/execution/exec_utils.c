/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:56:50 by abernade          #+#    #+#             */
/*   Updated: 2024/04/24 14:04:59 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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