/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:41:01 by abernade          #+#    #+#             */
/*   Updated: 2024/06/11 19:52:32 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_home(t_list *env)
{
	t_member	*home;

	home = get_env_element(env, "HOME");
	if (!home)
		return (NULL);
	return (home->value);
}

static char	*get_path(char **argv, t_list *env)
{
	int		argc;	
	char	*pathname;

	if (argv == NULL || argv[0] == NULL)
		return (NULL);
	argc = argv_size(argv);
	if (argc > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (NULL);
	}
	else if (argc <= 1)
	{
		pathname = get_home(env);
		if (!pathname)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (NULL);
		}
	}
	else
		pathname = argv[1];
	return (pathname);
}

static int	access_error(char *pathname)
{
	char	*errstr;

	if (access(pathname, F_OK))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(pathname, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	if (access(pathname, X_OK))
	{
		errstr = ft_strjoin("minishell: cd: ", pathname);
		perror(errstr);
		free(errstr);
		return (1);
	}
	return (0);
}

int	builtin_cd(char **av, t_list **env)
{
	char		*path;
	char		cwd[PATH_MAX];

	path = get_path(av, *env);
	if (path == NULL || access_error(path) == 1)
		return (1);
	if (getcwd(cwd, PATH_MAX) != NULL)
		update_env_element(env, "OLDPWD", ft_strdup(cwd));
	if (chdir(path) == -1)
	{
		perror("minishell: cd: ");
		return (1);
	}
	else if (getcwd(cwd, PATH_MAX) != NULL)
		update_env_element(env, "PWD", ft_strdup(cwd));
	return (0);
}
