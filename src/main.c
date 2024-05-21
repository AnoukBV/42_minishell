/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:58:43 by abernade          #+#    #+#             */
/*   Updated: 2024/05/21 15:11:57 by abernade         ###   ########.fr       */
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
	return (line);
}

static void	shell_prompt(t_list *env, int ac, char **envp)
{
	t_list		*tokens;
	char		*line;
	t_pipeline	*pipeline;	

	set_rl_signals();
	line = select_prompt();
	disable_signals();
	if (!line)
		return ;
	pipeline = parsing(line, &tokens, env);
	execute_pipeline(pipeline);
	if (line)
	{
		add_history(line);
		free(line);
		shell_prompt(env, ac, envp);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_list		*env;

	(void)av;
	env = NULL;
	set_hashtable(envp, &env);
	shell_prompt(env, ac, envp);
<<<<<<< HEAD
	ft_putstr_fd("exit\n", 1);
	free_env(env);	
=======
	ft_lstclear(&env, &del_member);	
>>>>>>> 7a2fa88f9525a557b5cf5ed2c7bf120370ecf7c6
	return (0);
}
