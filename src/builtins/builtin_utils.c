/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:19:16 by abernade          #+#    #+#             */
/*   Updated: 2024/05/15 18:59:00 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_envp(t_hashtable *envp)
{
	size_t	i;

	i = 0;
	printf("%d\n", envp->size);
	while (i < envp->size)
	{
		if (envp->member[i]->key != NULL)
			ft_printf("%s=%s\n", envp->member[i]->key, envp->member[i]->value);
		i++;
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
