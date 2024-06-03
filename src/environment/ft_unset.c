/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:45:14 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/03 17:03:18 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset_err_mess(char *wrong, char *to_free)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(wrong, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	if (to_free)
		free(to_free);
	return (1);
}
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
	{
		tmp = *env;
		*env = (*env)->next;
	}
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
		if (exp_check_err(argv[i + 1]) == 1)
			ft_unset_err_mess(argv[i + 1], NULL);
		else
			unset_variable(argv[i + 1], env);
		i++;
	}
	//printf("\n[ft_unset] (*env) after unset_variable: %p\n", *env);
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
