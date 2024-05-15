/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:45:14 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/15 11:35:10 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_variable(char *argv, t_hashtable *env, size_t size)
{
	t_member	*del;

	del = env_find_tmemb(env->member, argv, size);
	if (!del)
		return ;
	free(del->key);
	del->key = NULL;
	free(del->value);
	del->value = NULL;
}

void	ft_unset(t_pipeline	*p, t_command *cmd)
{
	t_hashtable	*env;
	char		**argv;
	size_t		i;

	env = *p->hash_env;
	argv = cmd->argv;
	i = 0;
	if (cmd->argv == NULL)
		return ;
	while (i < ft_arrlen(&argv[1]))
	{
		unset_variable(argv[i + 1], env, env->size);
		i++;
	}
}
