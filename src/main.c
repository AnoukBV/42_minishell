/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:58:43 by abernade          #+#    #+#             */
/*   Updated: 2024/05/29 17:05:31 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_status;

static char *get_prompt(void)
{
	char	*cwd;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		strerror(errno);
		exit(errno);
	}
	prompt = ft_strjoin(cwd, "$ ");
	free(cwd);
	return (prompt);
}

static char	*select_prompt(void)
{
	char			*prompt;
	char			*line;

	prompt = get_prompt();
	line = readline(prompt);
	free(prompt);
	return (line);
}

static void	shell_prompt(t_list *env, int ac)
{
	t_list		*tokens;
	char		*line;
	t_pipeline	*pipeline;

	set_rl_signals();
	line = select_prompt();
	set_exec_signals();
	if (ft_strlen(line))
	{
		pipeline = parsing(line, &tokens, env);
		pipeline->cmd_line = line;
		execute_pipeline(pipeline);
	}
	if (line)
	{
		add_history(line);
		free(line);
		env = pipeline->envp;
		//destroy pipeline ici??
		free(pipeline);
		shell_prompt(env, ac);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_list	*env;

	(void)av;
	g_status = 0;
	env = NULL;
	set_hashtable(envp, &env);
	shell_prompt(env, ac);
	return (0);
}
