/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:56:50 by abernade          #+#    #+#             */
/*   Updated: 2024/06/06 15:43:17 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_status(int status)
{
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}

static void	free_path_list(char	**path_list)
{
	char	**save;

	if (path_list == NULL)
		return ;
	save = path_list;
	while (*path_list != NULL)
	{
		free(*path_list);
		path_list++;
	}
	free(save);
}

static char	**path_check(t_list *env, char *name, t_pipeline *pipeline)
{
	char	**path_list;

	if (ft_strlen(name) == 0)
		return (NULL);
	path_list = get_path_list(env);
	if (!path_list)
		check_execve_error(name, pipeline);
	return (path_list);
}

t_bool	is_directory(const char *pathname)
{
	struct stat	file_info;

	stat(pathname, &file_info);
	return (!S_ISREG(file_info.st_mode));
}

char	*get_bin_path(t_list *env, char *name, t_pipeline *pipeline)
{
	char	**path_list;
	char	*cmd;
	char	*path;
	int		i;

	i = 0;
	path_list = path_check(env, name, pipeline);
	while (path_list && path_list[i] != NULL)
	{
		cmd = ft_strjoin("/", name);
		path = ft_strjoin(path_list[i], cmd);
		free(cmd);
		if (!access(path, F_OK) && !is_directory(path))
		{
			free_path_list(path_list);
			return (path);
		}
		free(path);
		i++;
	}
	free_path_list(path_list);
	return (NULL);
}
