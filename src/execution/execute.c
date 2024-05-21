/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:30:31 by abernade          #+#    #+#             */
/*   Updated: 2024/05/21 15:05:10 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern int	g_status;

static void	child_exec(t_pipeline *pipeline, t_command *cmd)
{
	char	**envp;
	char	*path;

	if (ft_strchr(cmd->command, '/') == NULL)
	{
		path = get_bin_path(pipeline->envp, cmd->command);
		if (path != NULL)
		{
			free(cmd->command);
			cmd->command = path;
		}
		else
			command_not_found_error(cmd->command, pipeline);
	}
	do_redirections(cmd, pipeline);
	close_fd_list(&pipeline->fd_list);
	check_execve_error(cmd->command, pipeline);
	envp = transform_envp(pipeline->envp);
	execve(cmd->command, cmd->argv, envp);
}

void static	builtin_exec(t_command *cmd, t_pipeline *pipeline, t_bool will_exit)
{
	int	exit_code;

	exit_code = 1;
	if (!ft_strncmp(cmd->command, "cd", 3))
		exit_code = builtin_cd(cmd->argv, pipeline->envp);
	else if (!ft_strncmp(cmd->command, "pwd", 4))
		exit_code = builtin_pwd();
	else if (!ft_strncmp(cmd->command, "echo", 5))
		exit_code = builtin_echo(cmd->argv);
	else if (!ft_strncmp(cmd->command, "export",7))
		exit_code = builtin_export(cmd->argv, pipeline->envp);
	g_status = exit_code;
	if (will_exit)
	{
		free(pipeline->cmd_line);
		free_env(pipeline->envp);
		destroy_pipeline(pipeline);
		exit(exit_code);
	}
}

void	fork_cmd(t_command *cmd, t_pipeline *pipeline)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		fork_error(pipeline);
	else if (pid == 0)
	{
		if (is_builtin(cmd->command))
			builtin_exec(cmd, pipeline, true);
		child_exec(pipeline, cmd);
		ft_putstr_fd("child_exec() returned :(\n", 2);
		exit (1) ;
	}
	add_pid(pid, &pipeline->pid_list);
}

void	execute_pipeline(t_pipeline *pipeline)
{
	t_command	*cmd;

	cmd = pipeline->cmd_list;
	prepare_pipeline(pipeline);
	while (cmd)
	{
		if (!cmd->prev && !cmd->next && is_builtin(cmd->command))
			builtin_exec(cmd, pipeline, false);
		else
			fork_cmd(cmd, pipeline);
		if (cmd->next == NULL)
		{
			close_fd_list(&pipeline->fd_list);
			wait_all_pid(&pipeline->pid_list);
		}
		cmd = cmd->next;
	}
	destroy_pipeline(pipeline);
}
