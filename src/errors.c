/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:48:23 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/23 16:24:23 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	redirection_error(t_pipeline *pipeline)
{
	perror(NULL);
	free(pipeline->cmd_line);
	free_env_list(&pipeline->envp);
	destroy_pipeline(pipeline);
	exit(1);
}

void	pipe_error(t_pipeline *pipeline)
{
	perror(NULL);
	free(pipeline->cmd_line);
	free_env_list(&pipeline->envp);
	destroy_pipeline(pipeline);
	exit(errno);
}

void	malloc_error(void)
{
	perror(NULL);
	exit(errno);
}
void	dup2_error(void)
{
	perror(NULL);
	exit(errno);
}

void	open_error(char *filename, t_pipeline *pipeline)
{
	char	*errstr;
	t_bool	will_exit;

	will_exit = (!(is_builtin(pipeline->cmd_list->command) \
			&& pipeline->cmd_list->prev == NULL \
			&& pipeline->cmd_list->next == NULL));
	errstr = ft_strjoin("minishell: ", filename);
	perror(errstr);
	free(errstr);
	if (will_exit)
	{
		free(pipeline->cmd_line);
		free_env_list(&pipeline->envp);
		destroy_pipeline(pipeline);
		exit(1);
	}
}

void	fork_error(t_pipeline *pipeline)
{
	(void)pipeline;
	/*
	*	todo
	*/
}

void	check_execve_error(char *pathname, t_pipeline *pipeline)
{
	char	*errstr;
	int		exit_code;

	exit_code = 0;
	if (access(pathname, F_OK))
		exit_code = 127;
	else if (access(pathname, X_OK))
		exit_code = 126;
	if (!exit_code)
		return ;
	errstr = ft_strjoin("minishell: ", pathname);
	perror(errstr);
	free(errstr);
	free(pipeline->cmd_line);
	free_env_list(&pipeline->envp);
	destroy_pipeline(pipeline);
	exit(exit_code);
}

void	command_not_found_error(char *name, t_pipeline *pipeline)
{
	char *errstr;

	errstr = ft_strjoin(name, ": command not found\n");
	ft_putstr_fd(errstr, 2);
	free(errstr);
	free_env_list(&pipeline->envp);
	free(pipeline->cmd_line);
	destroy_pipeline(pipeline);
	exit(127);
}
