/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:16:19 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/05 10:07:11 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_point(char *str)
{
	int	eq;

	eq = 0;
	while (str[eq] != '=' && str[eq])
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
		malloc_error();
	while (argv[i])
	{
		eq[i - 1] = split_point(argv[i]);
		i++;
	}
	return (eq);
}

int	ft_exp_err_mess(char *wrong, char *to_free)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(wrong, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	if (to_free)
		free(to_free);
	return (1);
}

int	ft_iscap(int a)
{
	if (!ft_isalpha(a))
		return (1);
	if (a <= 90 && a >= 65)
		return (1);
	return (0);
}

int	exp_check_err(char *str)
{
	size_t	i;

	i = 0;
	if (ft_isdigit(str[i]) || !str || !*str)
		return (1);
	while (str[i])
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
			return (1);
		i++;
	}
	return (0);
}
