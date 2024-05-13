/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:24:12 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/13 12:26:21 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_sort_entries(t_member **entries, int size)
{
	t_member	*curr;
	int	i;
	int		j;

	i = 1;
	while (i < size && entries[i - 1])
	{
		j = i - 1;
		curr = entries[i];
		while (j >= 0 && ft_strncmp(entries[j]->key, curr->key, \
			ft_strlen(entries[j]->key)) > 0)
		{
			entries[j + 1] = entries[j];
			j--;
		}
		entries[j + 1] = curr;
		i++;
	}
}

static void	print_memb_arr(t_member **m, int size)
{
	int	i;

	i = 0;
	while (i < size && m[i - 1])
	{
	  	if (!m[i])
			break ;
		if (ft_strncmp(m[i]->key, "_", ft_strlen(m[i]->key)))
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(m[i]->key, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(m[i]->value, 1);
			ft_putstr_fd("\"\n", 1);
		}
		i++;
	}
}

static int	export_prepare_sort(t_member **ent, t_member **env, int size)
{
	int	i;

	i = 0;
	while (i < size / 2 && env[i])
	{
		ent[i] = env[i];
		i++;
	}
	export_sort_entries(ent, size / 2);
	print_memb_arr(ent, size / 2);
	return (i);
}

void	ft_exp_p(t_hashtable **e)
{
	int			i;
	t_hashtable	*env;
	t_member	**entries;

	env = *e;
	entries = malloc(sizeof(t_member *) * env->size);
	if (!entries)
		return ;
	i = export_prepare_sort(entries, env->member, env->size);
	if (!env->member[i])
		return ;
	export_prepare_sort(entries, &env->member[i], env->size);
	free(entries);
}
