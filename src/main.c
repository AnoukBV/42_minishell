/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:58:43 by abernade          #+#    #+#             */
/*   Updated: 2024/04/29 02:15:03 by abernade         ###   ########.fr       */
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

static void	new_shell_line(char **envp, int ac)
{
	t_pipeline		*pipeline;
	char			*prompt;
	char			*line;

	set_rl_signals();
	prompt = get_prompt();
	line = readline(prompt);
	free(prompt);
	if (!line)
		return ;
	// tokens = NULL;
	// size = parsing(line, &tokens);
	// free_before_id(tokens, size);
	add_history(line);
	free(line);
	
	/*
	*	Execution
	*/
	pipeline = dummydata(envp);
	execute_pipeline(pipeline);
	new_shell_line(envp, ac);
}

int main(int ac, char **av, char **envp)
{
	(void)av;

	new_shell_line(envp, ac);
	return (0);
}

