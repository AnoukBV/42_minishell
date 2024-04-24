/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:58:43 by abernade          #+#    #+#             */
/*   Updated: 2024/04/24 12:57:01 by aboulore         ###   ########.fr       */
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
	size_t			size;

	set_rl_signals();
	prompt = get_prompt();
	line = readline(prompt);
	free(prompt);
	printf("string: %s\n", line); // TO BE DELETED
	tokens = NULL;
	size = parsing(line, &tokens);
	free_before_id(tokens, size);
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
