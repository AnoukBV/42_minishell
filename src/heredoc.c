/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 08:02:27 by abernade          #+#    #+#             */
/*   Updated: 2024/06/05 14:31:37 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern int	g_status;

static char	*get_heredoc_name(void)
{
	char	*filename;
	char	*nb;
	int		i;

	i = 0;
	nb = ft_itoa(i);
	filename = ft_strjoin("heredoc", nb);
	free(nb);
	while (!access(filename, F_OK) && i < MAX_HEREDOC)
	{
		i++;
		free(filename);
		nb = ft_itoa(i);
		filename = ft_strjoin("heredoc", nb);
		free(nb);
	}
	if (i == MAX_HEREDOC)
	{
		ft_putstr_fd("heredoc error\n", 2);
		exit(1);
	}
	return(filename);
}

static void	write_heredoc(int fd, const char *delimiter, char *filename)
{
	t_bool	eof;
	char	*line;

	g_status = 0;
	eof = false;
	while (!eof)
	{
		set_heredoc_signals();
		line = readline("> ");
		if (!line)
		{
			heredoc_eof_warning(delimiter);
			free(filename);
			exit(2);
		}
		eof = (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0);
		if (!eof)
		{
			if (line)
				ft_putstr_fd(line, fd);
			ft_putstr_fd("\n", fd);
		}
	}
}

static void	create_heredoc(char *filename, const char *delimiter)
{
	int	fd;

	fd = open(filename, O_CREAT | O_APPEND | O_RDWR, 00770);
	if (fd == -1)
		simple_generic_error();
	write_heredoc(fd, delimiter, filename);
	if (close(fd))
		simple_generic_error();
}

static void	handle_child_exit(int status, char **filename, t_list **envp)
{
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status))
		{
			free(*filename);
			*filename = NULL;
		}
		if (WEXITSTATUS(status) == 2 || WEXITSTATUS(status) == 0)
			update_env_exit_code(envp, 0);
	}
	else if (WIFSIGNALED(status))
	{
		free(*filename);
		*filename = NULL;		
		update_env_exit_code(envp, WTERMSIG(status) + 128);
	}
}

char	*new_heredoc(const char *delimiter, t_list **envp)
{
	char	*filename;
	int		status;
	int		pid;

	filename = get_heredoc_name();
	pid = fork();
	if (pid == -1)
		simple_generic_error();
	if (pid == 0)
		create_heredoc(filename, delimiter);
	waitpid(pid, &status, 0);
	handle_child_exit(status, &filename, envp);
	return (filename);
}
