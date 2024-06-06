/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:41:47 by abernade          #+#    #+#             */
/*   Updated: 2024/06/05 14:29:06 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**rm_argv(char *filename)
{
	char	**argv;

	argv = malloc(sizeof(char*) * 4);
	if (!argv)
		malloc_error();
	argv[0] = ft_strdup("/usr/bin/rm");
	argv[1] = ft_strdup("-rf");
	argv[2] = ft_strdup(filename);
	argv[3] = NULL;
	return (argv);
}

void	delete_heredoc(char *filename, t_list *env)
{
	char	**envp;
	char	**argv;
	int		pid;

	pid = fork();
	if (pid == -1)
		simple_generic_error();
	if (pid == 0)
	{
		argv = rm_argv(filename);
		envp = transform_envp(env);
		execve("/usr/bin/rm", argv, envp);
		ft_putstr_fd("failed to remove heredoc\n", 2);
		exit(1);
	}
	waitpid(pid, NULL, 0);
}
