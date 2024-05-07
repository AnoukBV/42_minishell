/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:58:43 by abernade          #+#    #+#             */
/*   Updated: 2024/05/07 16:23:11 by aboulore         ###   ########.fr       */
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

char	*select_prompt(void)
{
	static size_t	count = 0;
	static char		**inputs = NULL;
	size_t			size;
	char			*prompt;
	char			*line;

	line = NULL;
	if (inputs == NULL)
	{
		prompt = get_prompt();
		line = readline(prompt);
		free(prompt);
		if (ft_strlen(line) == 0)
			return (NULL);
		inputs = newlines(line, &size);
	}
	line = inputs[count];
	count += 1;
	if (!inputs[count])
	{
		free(inputs);
		count = 0;
		inputs = NULL;
	}
	return (line);;
}

static void	shell_prompt(t_hashtable *env, int ac, char **envp)
{
	t_list		*tokens;
	char		*line;
	t_pipeline	*pipeline;	

	set_rl_signals();
	tokens = NULL;
	line = select_prompt();
	if (!line)
		return ;
	parsing(line, &tokens, env);
	pipeline = dummydata(envp);
	execute_pipeline(pipeline);
	printf("\nexit code: %d\n", g_status);
	if (line)
	{
		add_history(line);
		free(line);
		shell_prompt(env, ac, envp);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_hashtable		*env;

	(void)av;
	env = NULL;
	set_hashtable(envp, &env);
	shell_prompt(env, ac, envp);
	free_env(env);	
	return (0);
}

