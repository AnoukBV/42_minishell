/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:16:19 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/16 13:35:54 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_point(char *str)
{
	int	eq;

	eq = 0;
	while (str[eq] != '=')
		eq++;
	return (eq);
}

int	*split_key_value(char **argv)
{
	size_t	i;
	int		*eq;

	i = 1;
	eq = malloc(sizeof(int) * ft_arrlen(&argv[i]));
	if (!eq)
		return (NULL);
	while (argv[i])
	{
		//if (argv[i][0] == '=')
			//-bash: export: `=blabla': not a valid identifier, mais pas quitter, si des args sont valides on s'n occupe
		eq[i - 1] = split_point(argv[i]);
		i++;
	}
	return (eq);
}
/*
t_member	*env_fetch_member(t_member **member, size_t size)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		if (!member[i])
		{
			member[i] = ft_calloc(sizeof(t_member), 1);
			return (member[i]);
		}
		i++;
	}
	return (NULL);
}
*/
int	ft_iscap(int a)
{
	if (!ft_isalpha(a))
		return (1);
	if (a <= 90 && a >= 65)
		return (1);
	return (0);
}

void	exp_check_err(char *str)
{
	size_t	i;

	i = 0;
	if (ft_isdigit(str[i]))
		//ERROR
	while (str[i])
	{
		if (ft_iscap(str[i]) && (str[i] != '_' || !ft_isalnum(str[i])))
			//ERROR
		i++;
	}
}
