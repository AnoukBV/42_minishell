/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:30:31 by abernade          #+#    #+#             */
/*   Updated: 2024/06/26 08:42:19 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_exec(t_pipeline *pipeline, t_command *cmd)
{
	char	**envp;
	char	*path;

	do_redirections(cmd, pipeline);
	if (cmd->command && ft_strchr(cmd->command, '/') == NULL && \
		!is_builtin(cmd->command))
	{
		path = get_bin_path(pipeline->envp, cmd->command, pipeline);
		if (path != NULL)
		{
			free(cmd->command);
			cmd->command = path;
		}
		else
			command_not_found_error(cmd->command, pipeline);
	}
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

static void	handle_child(t_command *cmd, t_pipeline *pipeline)
{
	if (cmd->prev)
		close(cmd->pipe_left[1]);
	if (cmd->next)
		close(cmd->pipe_right[0]);
	child_exec(pipeline, cmd);
	if (cmd->command == NULL)
	{
		free(pipeline->cmd_line);
		free_env_list(&pipeline->envp);
		destroy_pipeline(pipeline, EXIT);
	}
	exit(0);
}

static void	fork_cmd(t_command *cmd, t_pipeline *pipeline)
{
	int	pid;

	set_pipes(pipeline, cmd);
	pid = fork();
	if (pid == -1)
		generic_error(pipeline);
	else if (pid == 0)
		handle_child(cmd, pipeline);
	if (cmd->prev)
		close(cmd->pipe_left[0]);
	if (cmd->next)
		close(cmd->pipe_right[1]);
	add_pid(pid, &pipeline->pid_list);
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
	destroy_pipeline(pipeline, STAY);
}
