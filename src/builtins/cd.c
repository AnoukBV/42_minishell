/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:41:01 by abernade          #+#    #+#             */
/*   Updated: 2024/05/13 16:16:21 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	av_size(char **av)
{
	int	i;

	if (!av)
		return (0);
	i = 0;
	while (av[i])
		i++;
	return (i);
}

static char	*get_home(t_hashtable *env)
{
	t_member	*home;

	home = get_env_element(env, "HOME");
	if (!home)
		return (NULL);
	return (home->value);
}

static char	*get_path(char *pathname, char **av, t_hashtable *env)
{
	int		ac;	
	char	*home;

	ac = av_size;
	if (ac >= 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments", 2);
		return (NULL);
	}
	else if (ac == 0)
	{
		home = get_home(env);
		if (!home)
		{
			ft_putstr_fd("minishell: cd: HOME not set", 2);
			return (NULL);
		}
	}
	else
		home = pathname;
	return (home);
}

static int	access_error(char *pathname)
{
	char	*errstr;

	if (access(pathname, F_OK) || access(pathname, X_OK))
	{
		ft_strjoin("minishell: cd: ", pathname);
		perror(errstr);
		free(errstr);
		return (1);
	}
	return (0);
}

/*
*	Returned value is meant to be the exit code if run in a child process
*/
int	builtin_cd(char *pathname, char **av, t_hashtable *env)
{
	char	*path;

	path = get_path(pathname, av, env);
	if (path == NULL || access_error(pathname))
		return (1);
	if (chdir(path) == -1)
	{
		perror("minishell: cd: ");
		return (1);
	}
	return (0);
}
