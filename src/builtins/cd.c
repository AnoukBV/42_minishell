/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:41:01 by abernade          #+#    #+#             */
/*   Updated: 2024/05/15 15:27:55 by abernade         ###   ########.fr       */
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

static char	*get_path(char **av, t_hashtable *env)
{
	int		ac;	
	char	*pathname;

	if (!av || av[0] == NULL)
		return (NULL);
	ac = av_size(av);
	if (ac > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments", 2);
		return (NULL);
	}
	else if (ac < 1)
	{
		pathname = get_home(env);
		if (!pathname)
		{
			ft_putstr_fd("minishell: cd: HOME not set", 2);
			return (NULL);
		}
	}
	else
		pathname = av[1];
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
*	Returned value is meant to be the exit code
*/
int	builtin_cd(char **av, t_hashtable *env)
{
	char	*path;

	path = get_path(av, env);
	if (path == NULL || access_error(path))
		return (1);
	if (chdir(path) == -1)
	{
		perror("minishell: cd: ");
		return (1);
	}
	return (0);
}
