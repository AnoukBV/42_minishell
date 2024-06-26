/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:53:39 by abernade          #+#    #+#             */
/*   Updated: 2024/06/26 07:45:40 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exec(t_command *cmd, t_pipeline *pipeline, t_bool will_exit)
{
	int	exit_code;

	exit_code = 1;
	if (!ft_strncmp(cmd->command, "cd", 3))
		exit_code = builtin_cd(cmd->argv, &pipeline->envp);
	else if (!ft_strncmp(cmd->command, "pwd", 4))
		exit_code = builtin_pwd();
	else if (!ft_strncmp(cmd->command, "echo", 5))
		exit_code = builtin_echo(cmd->argv);
	else if (!ft_strncmp(cmd->command, "exit", 5))
		exit_code = builtin_exit(pipeline, cmd);
	else if (!ft_strncmp(cmd->command, "export", 7))
		exit_code = ft_export(&pipeline->envp, cmd->argv);
	else if (!ft_strncmp(cmd->command, "env", 4))
		exit_code = print_env(&pipeline->envp, cmd->argv, ENV);
	else if (!ft_strncmp(cmd->command, "unset", 6))
		exit_code = ft_unset(cmd->argv, &pipeline->envp);
	update_env_exit_code(&pipeline->envp, exit_code);
	if (will_exit)
	{
		free(pipeline->cmd_line);
		free_env_list(&pipeline->envp);
		destroy_pipeline(pipeline, EXIT);
		exit(exit_code);
	}
}

void	simple_builtin_exec(t_command *cmd, t_pipeline *pipeline)
{
	int	stdout_fd_save;
	int	stdin_fd_save;

	stdout_fd_save = dup(1);
	stdin_fd_save = dup(0);
	if (do_redirections(cmd, pipeline) == 0)
	{
		close_fd_list(&pipeline->fd_list);
		builtin_exec(cmd, pipeline, false);
	}
	else
		update_env_exit_code(&pipeline->envp, 1);
	dup2(stdout_fd_save, 1);
	dup2(stdin_fd_save, 0);
}
