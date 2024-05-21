/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:41:01 by abernade          #+#    #+#             */
/*   Updated: 2024/05/21 15:07:16 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_home(t_hashtable *env)
{
	t_member	*home;

	home = get_env_element(env, "HOME");
	if (!home)
		return (NULL);
	return (home->value);
}

static char	*get_path(char **argv, t_hashtable *env)
{
	int		argc;	
	char	*pathname;

	if (argv == NULL || argv[0] == NULL)
		return (NULL);
	argc = argv_size(argv);
	if (argc > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments", 2);
		return (NULL);
	}
	else if (argc <= 1)
	{
		pathname = get_home(env);
		if (!pathname)
		{
			ft_putstr_fd("minishell: cd: HOME not set", 2);
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

	if (access(pathname, F_OK) || access(pathname, X_OK))
	{
		errstr = ft_strjoin("minishell: cd: ", pathname);
		perror(errstr);
		free(errstr);
		return (1);
	}
	return (0);
}

/*
*	Returned value is meant to be used as the exit code
*/
int	builtin_cd(char **av, t_hashtable *env)
{
	char		*path;
	char		cwd[PATH_MAX];
	// t_member	*env_element;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (1);
	path = get_path(av, env);
	if (path == NULL || access_error(path) == 1)
		return (1);
	if (chdir(path) == -1)
	{
		perror("minishell: cd: ");
		return (1);
	}
	else
	{
		/*
		*	To do: set PWD and OLDPWD values
		*/
	}
	return (0);
}
