/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:48:45 by abernade          #+#    #+#             */
/*   Updated: 2024/05/30 16:35:02 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_bool	is_number(char *str)
{
	if (!str)
		return (true);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

void	builtin_exit(t_pipeline *pipeline, t_command *cmd)
{
	int		exit_code;
	char	**argv;

	argv = cmd->argv;
	if (!argv[1])
		exit_code = 0;
	else if (!is_number(argv[1]))
	{
		exit_code = 2;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	else
		exit_code = ft_atoi(argv[1]);
	if (!cmd->next && !cmd->prev)
		ft_putstr_fd("exit\n", 1);
	free(pipeline->cmd_line);
	free_env_list(&pipeline->envp);
	destroy_pipeline(pipeline);
	exit(exit_code);
}
