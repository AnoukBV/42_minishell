/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:30:31 by abernade          #+#    #+#             */
/*   Updated: 2024/06/05 12:30:08 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void static	builtin_exec(t_command *cmd, t_pipeline *pipeline, t_bool will_exit)
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
		builtin_exit(pipeline, cmd);
	else if (!ft_strncmp(cmd->command, "export" ,7))
		exit_code = ft_export(&pipeline->envp, cmd->argv);
	else if (!ft_strncmp(cmd->command, "env" , 4))
		exit_code = print_env(&pipeline->envp, ENV);
	else if (!ft_strncmp(cmd->command, "unset" ,6))
		exit_code = ft_unset(cmd->argv, &pipeline->envp);
	update_env_exit_code(&pipeline->envp, exit_code);
	if (will_exit)
	{
		free(pipeline->cmd_line);
		free_env_list(&pipeline->envp);
		destroy_pipeline(pipeline);
		exit(exit_code);
	}
}

static void	child_exec(t_pipeline *pipeline, t_command *cmd)
{
	char	**envp;
	char	*path;

	if (cmd->command && ft_strchr(cmd->command, '/') == NULL && \
		!is_builtin(cmd->command))
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
	if (is_builtin(cmd->command))
			builtin_exec(cmd, pipeline, true);
	else if (cmd->command != NULL)
	{
		check_execve_error(cmd->command, pipeline);
		envp = transform_envp(pipeline->envp);
		execve(cmd->command, cmd->argv, envp);
	}
}

static void	fork_cmd(t_command *cmd, t_pipeline *pipeline)
{
	int	pid;

	set_pipes(pipeline, cmd);
	pid = fork();
	if (pid == -1)
		generic_error(pipeline);
	else if (pid == 0)
	{
		child_exec(pipeline, cmd);
		exit(0) ;
	}
	if (cmd->prev)
		close(cmd->pipe_left[0]);
	if (cmd->next)
		close(cmd->pipe_right[1]);
	add_pid(pid, &pipeline->pid_list);
}

static void	simple_builtin_exec(t_command *cmd, t_pipeline *pipeline)
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
	dup2(stdout_fd_save , 1);
	dup2(stdin_fd_save , 0);
}

void	execute_pipeline(t_pipeline *pipeline)
{
	t_command	*cmd;

	cmd = pipeline->cmd_list;
	while (cmd)
	{
		if (!cmd->prev && !cmd->next && is_builtin(cmd->command))
			simple_builtin_exec(cmd, pipeline);
		else
			fork_cmd(cmd, pipeline);
		if (cmd->next == NULL)
		{
			close_fd_list(&pipeline->fd_list);
			wait_all_pid(&pipeline->pid_list, &pipeline->envp);
		}
		cmd = cmd->next;
	}
	destroy_pipeline(pipeline);
}
