/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:55:09 by abernade          #+#    #+#             */
/*   Updated: 2024/07/02 11:04:21 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

char	*get_prompt(t_bool clear)
{
	static char	*last_cwd = NULL;
	char		*cwd;
	char		*prompt;

	if (clear)
	{
		if (last_cwd)
			free(last_cwd);
		return (NULL);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd && !last_cwd)
		exit(errno);
	if (!cwd)
		cwd = ft_strdup(last_cwd);
	else
	{
		if (last_cwd)
			free(last_cwd);
		last_cwd = ft_strdup(cwd);
	}
	prompt = ft_strjoin(cwd, "$ ");
	free(cwd);
	return (prompt);
}

char	*select_prompt(void)
{
	char	*prompt;
	char	*line;

	set_rl_signals();
	prompt = get_prompt(false);
	line = readline(prompt);
	set_exec_signals();
	free(prompt);
	return (line);
}

static int	prepare_next_input(char *line, t_pipeline *pipeline, t_list **env)
{
	int	exit = 0;

	if (ft_strlen(line))
	{
		add_history(line);
		free(line);
		if (pipeline)
		{
			*env = pipeline->envp;
			free(pipeline);
		}
		shell_prompt(env);
	}
	else if (line)
	{
		free(line);
		shell_prompt(env);
	}
	exit = ft_atoi(env_find_key(ENV_EXIT_CODE, env));
	return (exit);
}

int	shell_prompt(t_list **env)
{
	t_list		*tokens;
	char		*line;
	t_pipeline	*pipeline;
	int			exit;

	line = select_prompt();
	pipeline = NULL;
	if (g_status)
	{
		update_env_exit_code(env, g_status + 128);
		g_status = 0;
	}
	if (ft_strlen(line))
	{
		if (parsing(ft_strdup(line), &tokens, *env, &pipeline) == 0)
		{
			pipeline->cmd_line = line;
			execute_pipeline(pipeline);
		}
	}
	exit = prepare_next_input(line, pipeline, env);
	return (exit);
}
