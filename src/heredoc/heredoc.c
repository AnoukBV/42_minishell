/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 08:02:27 by abernade          #+#    #+#             */
/*   Updated: 2024/06/11 12:34:30 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern int	g_status;

static void	exit_heredoc(int exit_code, t_command **cmd, \
	t_list **envp, char *path)
{
	destroy_cmd_list(cmd, false);
	free_env_list(envp);
	free(path);
	clear_statics();
	exit(exit_code);
}

static void	write_heredoc(int fd, const char *delimiter)
{
	t_bool	eof;
	char	*line;

	eof = false;
	while (!eof)
	{
		set_heredoc_signals();
		line = readline("> ");
		if (!line && g_status != SIGINT)
		{
			heredoc_eof_warning(delimiter);
			eof = true;
		}
		else
			eof = (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0);
		if (!eof)
		{
			if (line)
				ft_putstr_fd(line, fd);
			ft_putstr_fd("\n", fd);
		}
		if (g_status == SIGINT)
			eof = true;
		free(line);
	}
}

static void	create_heredoc(char *filename, const char *delimiter)
{
	int	fd;

	fd = open(filename, O_CREAT | O_APPEND | O_RDWR, 00770);
	if (fd == -1)
		simple_generic_error();
	write_heredoc(fd, delimiter);
	if (close(fd))
		simple_generic_error();
}

static void	handle_child_exit(int status, char **filename, t_list **envp)
{
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) != 0)
		{
			unlink(*filename);
			free(*filename);
			*filename = NULL;
			update_env_exit_code(envp, WEXITSTATUS(status) + 128);
		}
		else
			update_env_exit_code(envp, 0);
	}
	else if (WIFSIGNALED(status))
	{
		unlink(*filename);
		free(*filename);
		*filename = NULL;
		update_env_exit_code(envp, WTERMSIG(status) + 128);
	}
}

char	*new_heredoc(const char *delimiter, t_list **envp, t_command **cmd)
{
	char	*filename;
	int		status;
	int		pid;

	filename = get_heredoc_name();
	disable_signals();
	pid = fork();
	if (pid == -1)
		simple_generic_error();
	if (pid == 0)
	{
		create_heredoc(filename, delimiter);
		if (g_status == SIGINT)
			exit_heredoc(2, cmd, envp, filename);
		else
			exit_heredoc(0, cmd, envp, filename);
	}
	waitpid(pid, &status, 0);
	set_exec_signals();
	handle_child_exit(status, &filename, envp);
	return (filename);
}
