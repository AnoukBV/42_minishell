/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:11:19 by abernade          #+#    #+#             */
/*   Updated: 2024/06/05 12:17:05 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	char	*errstr;

	errstr = ft_strjoin(name, ": command not found\n");
	ft_putstr_fd(errstr, 2);
	free(errstr);
	free_env_list(&pipeline->envp);
	free(pipeline->cmd_line);
	destroy_pipeline(pipeline);
	exit(127);
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

void	generic_error(t_pipeline *pipeline)
{
	perror(NULL);
	free_env_list(&pipeline->envp);
	destroy_pipeline(pipeline);
	exit(1);
}

void	simple_generic_error(void)
{
	perror(NULL);
	exit(1);
}
