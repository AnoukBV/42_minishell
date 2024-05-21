/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:45:14 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/16 14:01:58 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_variable(char *argv, t_list *env)
{
	t_member	*del;
	t_list		*tmp;
	t_list		*prev;
	
	tmp = env;
	prev = tmp;
	del = env_find_tmemb(argv, &env);
	if (!del || !tmp)
		return ;
	while (tmp && tmp->content != del)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp)
		prev->next = tmp->next;
	else
		prev->next = NULL;
	ft_lstdelone(tmp, &del_member);
}

void	ft_unset(t_pipeline	*p, t_command *cmd)
{
	t_list	*env;
	char		**argv;
	size_t		i;

	env = p->envp;
	argv = cmd->argv;
	i = 0;
	if (cmd->argv == NULL)
		return ;
	while (i < ft_arrlen(&argv[1]))
	{
		unset_variable(argv[i + 1], env);
		i++;
	}
}
