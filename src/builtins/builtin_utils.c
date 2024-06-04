/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:19:16 by abernade          #+#    #+#             */
/*   Updated: 2024/06/04 14:58:03 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_envp(t_list *envp)
{
	t_member	*env_elem;

	while (envp)
	{
		env_elem = envp->content;
		ft_printf("%s=%s\n", env_elem->key, env_elem->value);
		envp = envp->next;
	}
}

int	argv_size(char **av)
{
	int	i;

	if (!av)
		return (0);
	i = 0;
	while (av[i])
		i++;
	return (i);
}

t_bool	is_builtin(char *cmd_name)
{
	if (!cmd_name)
	return (false);
	return (!ft_strncmp(cmd_name, "echo", 5) \
		|| !ft_strncmp(cmd_name, "cd", 3) \
		|| !ft_strncmp(cmd_name, "pwd", 4) \
		|| !ft_strncmp(cmd_name, "export", 7) \
		|| !ft_strncmp(cmd_name, "unset", 6) \
		|| !ft_strncmp(cmd_name, "env", 4) \
		|| !ft_strncmp(cmd_name, "exit", 5));
}
