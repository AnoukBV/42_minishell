/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 08:02:27 by abernade          #+#    #+#             */
/*   Updated: 2024/06/05 11:20:04 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern int	g_status;

static int event(void)
{
	return (0);
}

static void	addline(const char *line, int fd)
{
	if (line)
		ft_putstr_fd(line, fd);
	ft_putstr_fd("\n", fd);
}

static char	*get_heredoc_name(void)
{
	char	*filename;
	int		i;

	i = 0;
	filename = ft_strjoin("heredoc", ft_itoa(i));
	while (!access(filename, F_OK) && i < MAX_HEREDOC)
	{
		i++;
		free(filename);
		filename = ft_strjoin("heredoc", ft_itoa(i));
	}
	if (i == MAX_HEREDOC)
	{
		ft_putstr_fd("heredoc error\n", 2);
		exit(1);
	}
	return(filename);
}

static int	write_heredoc(int fd, const char *delimiter, t_list **envp)
{
	t_bool	eof;
	char	*line;

	g_status = 0;
	eof = false;
	rl_event_hook = event;
	while (!eof)
	{
		line = readline("> ");
		if (g_status)
		{
			update_env_exit_code(envp, g_status + 128);
			return (-1);
		}
		if (!line)
		{
			heredoc_eof_warning(delimiter);
			update_env_exit_code(envp, 0);
			return (-1);
		}
		eof = (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0);
		if (!eof)
			addline(line, fd);
	}
	return (0);
}

char	*new_heredoc(const char *delimiter, t_list **envp)
{
	char	*filename;
	int		fd;

	filename = get_heredoc_name();
	fd = open(filename, O_CREAT | O_APPEND | O_RDWR);
	if (fd == -1)
		simple_generic_error();
	set_heredoc_signals();
	if (write_heredoc(fd, delimiter, envp))
	{
		free(filename);
		return (NULL);
	}
	signals_default();
	if (close(fd))
		simple_generic_error();
	return (filename);
}
