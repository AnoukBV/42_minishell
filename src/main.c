/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:58:43 by abernade          #+#    #+#             */
/*   Updated: 2024/04/24 14:08:22 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char *get_prompt(void)
{
	char	*cwd;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if(!cwd)
	{
		strerror(errno);
		exit(errno);
	}
	prompt = ft_strjoin(cwd, "$ ");
	free(cwd);
	return (prompt);
}

static void	shell_prompt(char **envp, int ac)
{
	t_list			*tokens;
	char			*prompt;
	char			*line;
	static char			**inputs = NULL;
	static size_t		count	= 0;
	size_t			size;

	set_rl_signals();
	line = NULL;
	if (inputs == NULL)
	{
		prompt = get_prompt();
		line = readline(prompt);
		free(prompt);
		inputs = newlines(line, &size);
	}
	printf("string: %s\n", line); // TO BE DELETED
	tokens = NULL;
	parsing(inputs[count], &tokens);
	free_before_id(tokens, 1);
	count += 1;
	if (!inputs[count])
	{
		free(inputs);
		count = 0;
		inputs = NULL;
	}
	/*
	*	Execution
	*/
	tokens = NULL;

	if (line)
	{
		add_history(line);
		free(line);
		shell_prompt(envp, ac);
	}
}

int main(int ac, char **av, char **envp)
{
	(void)av;

	shell_prompt(envp, ac);
	return (0);
}
