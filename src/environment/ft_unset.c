/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:45:14 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/29 15:59:47 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_variable(char *argv, t_list **env)
{
	t_member	*del;
	t_list		*tmp;
	t_list		*prev;
	
	tmp = *env;
	prev = tmp;
	del = env_find_tmemb(argv, env);
	if (!del || !tmp)
		return ;
	while (tmp && tmp->content != del)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (prev == *env && tmp)
		*env = (*env)->next;
	else if (tmp)
		prev->next = tmp->next;
	else
		prev->next = NULL;
	ft_lstdelone(tmp, &del_member);
}

int	ft_unset(char **argv, t_list **env)
{
	size_t		i;

	i = 0;
	if (argv == NULL)
		return (1);
	while (i < ft_arrlen(&argv[1]))
	{
		unset_variable(argv[i + 1], env);
		i++;
	}
	printf("\n[ft_unset] (*env) after unset_variable: %p\n", *env);
	return (0);
}

int	ft_exp_option_mess(char str)
{
	ft_putstr_fd("minishell: export: -", 2);
	ft_putchar_fd(str, 2);
	ft_putstr_fd(": invalid option\nexport: usage: export", 2);
	ft_putstr_fd("[name[=value] ...]\n", 2);
	return (1);
}
