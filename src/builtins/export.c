/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:15:55 by abernade          #+#    #+#             */
/*   Updated: 2024/05/21 15:38:25 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_export(char **argv, t_list *envp)
{
	int	argc;
	
	argc = argv_size(argv);
	if(argc == 1)
		print_envp(envp);
	return (0);
}
