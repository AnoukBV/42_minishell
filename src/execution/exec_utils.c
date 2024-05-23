/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:56:50 by abernade          #+#    #+#             */
/*   Updated: 2024/05/23 18:03:27 by abernade         ###   ########.fr       */
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

t_bool	is_builtin(char *cmd_name)
{
	return (!ft_strncmp(cmd_name, "echo", 5) \
		|| !ft_strncmp(cmd_name, "cd", 3) \
		|| !ft_strncmp(cmd_name, "pwd", 4) \
		|| !ft_strncmp(cmd_name, "export", 7) \
		|| !ft_strncmp(cmd_name, "unset", 6) \
		|| !ft_strncmp(cmd_name, "env", 4) \
		|| !ft_strncmp(cmd_name, "exit", 5));
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

char	*get_bin_path(t_list *env, char *name)
{
	char	**path_list;
	char	*cmd;
	char	*path;
	int		i;

	if (ft_strlen(name) == 0)
		return (NULL);
	path_list = get_path_list(env);
	i = 0;
	while (path_list[i] != NULL)
	{
		cmd = ft_strjoin("/", name);
		path = ft_strjoin(path_list[i], cmd);
		free(cmd);
		if (!access(path, F_OK))
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
