/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:58:43 by abernade          #+#    #+#             */
/*   Updated: 2024/05/02 15:10:31 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

static void	shell_prompt(t_hashtable *env, int ac)
{
	t_list			*tokens;
	char			*line;

	set_rl_signals();		//demander a Arthur pour free l'env
	tokens = NULL;
	line = select_prompt();
	if (!line)
		shell_prompt(env, ac);
	printf("string: %s\n", line); // TO BE DELETED
	parsing(line, &tokens, env);
	/*
	*	Execution
	*/
	if (line)
	{
		add_history(line);
		free(line);
		shell_prompt(env, ac);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_hashtable		*env;

	(void)av;
	env = NULL;
	set_hashtable(envp, &env);
	shell_prompt(env, ac);
	return (0);
}
