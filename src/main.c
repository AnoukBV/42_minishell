/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:58:43 by abernade          #+#    #+#             */
/*   Updated: 2024/05/01 17:50:46 by abernade         ###   ########.fr       */
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
	return (line);
}

static void	shell_prompt(char **envp, int ac)
{
	t_list			*tokens;
	char			*line;

	set_rl_signals();
	tokens = NULL;
	line = select_prompt();
	if (!line)
		shell_prompt(envp, ac);
	printf("string: %s\n", line); // TO BE DELETED
	parsing(line, &tokens);
	free_before_id(tokens, 1);
	/*
	*	Execution
	*/
	if (line)
	{
		add_history(line);
		free(line);
		shell_prompt(envp, ac);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_hashtable		*env;

	(void)av;
	set_hashtable(envp, &env);
	shell_prompt(envp, ac);
	free_env(env);	
	return (0);
}

