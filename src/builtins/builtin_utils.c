/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:19:16 by abernade          #+#    #+#             */
/*   Updated: 2024/05/21 15:43:39 by abernade         ###   ########.fr       */
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
