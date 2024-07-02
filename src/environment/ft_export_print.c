/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:24:12 by aboulore          #+#    #+#             */
/*   Updated: 2024/07/02 09:46:55 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_sort_entries(t_member **entries, int size)
{
	t_member	*curr;
	int			i;
	int			j;

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
	while (i < size && m[i])
	{
		if (!m[i])
			break ;
		if (ft_strncmp(m[i]->key, "_", ft_strlen(m[i]->key)) && \
			ft_strncmp(m[i]->key, ENV_EXIT_CODE, ft_strlen(ENV_EXIT_CODE)))
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(m[i]->key, 1);
			if (!m[i]->value)
				ft_putstr_fd("\n", 1);
			else
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(m[i]->value, 1);
				ft_putstr_fd("\"\n", 1);
			}
		}
		i++;
	}
}

static t_list	*export_prepare_sort(t_member **ent, t_list **env)
{
	int			i;
	t_list		*tmp;

	i = 0;
	tmp = *env;
	if (!tmp)
		return (0);
	while (tmp)
	{
		ent[i] = (t_member *)tmp->content;
		tmp = tmp->next;
		i++;
	}
	export_sort_entries(ent, i);
	print_memb_arr(ent, i);
	return (tmp);
}

int	ft_exp_p(t_list **e)
{
	t_list		*env;
	t_member	**entries;

	env = *e;
	entries = ft_calloc(ft_lstsize(env) + 1, sizeof(t_member *));
	if (!entries)
		malloc_error();
	env = export_prepare_sort(entries, &env);
	free(entries);
	return (0);
}
