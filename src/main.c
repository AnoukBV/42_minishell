/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:58:43 by abernade          #+#    #+#             */
/*   Updated: 2024/06/05 15:14:07 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_status;

void	shell_prompt(t_list **env);

static char	*get_prompt(void)
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

char	*select_prompt(void)
{
	char	*prompt;
	char	*line;
	
	prompt = get_prompt();
	line = readline(prompt);
	free(prompt);
	return (line);
}

static int	prepare_next_input(char *line, t_pipeline *pipeline, t_list **env)
{
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
	return (0);
}

void	shell_prompt(t_list **env)
{
	t_list		*tokens;
	char		*line;
	t_pipeline	*pipeline;

	set_rl_signals();
	line = select_prompt();
	set_exec_signals();
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
		else
			pipeline = NULL;
	}
	prepare_next_input(line, pipeline, env);
}

int	main(int ac, char **av, char **envp)
{
	t_list	*env;

	(void)av;
	(void)ac;
	g_status = 0;
	env = NULL;
	set_hashtable(envp, &env);
	shell_prompt(&env);
	ft_lstclear(&env, &del_member);
	ft_putstr_fd("exit\n", 1);
	return (0);
}
