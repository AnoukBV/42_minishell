/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:24:12 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/16 14:10:54 by aboulore         ###   ########.fr       */
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

static t_list	*export_prepare_sort(t_member **ent, t_list **env)
{
	int			i;
	t_list		*tmp;
	t_member	*m;
	char		c;

	i = 0;
	tmp = *env;
	if (!tmp)
		return (0);
	m = (t_member *)tmp->content;
	c = m->key[0];
	while (tmp && ft_iscap(c) && c != '_')
	{
		m = (t_member *)tmp->content;
		c = m->key[0];
		ent[i] = (t_member *)tmp->content;
		tmp = tmp->next;
		i++;
	}
	export_sort_entries(ent, i);
	print_memb_arr(ent, i);
	return (tmp);
}

void	ft_exp_p(t_list **e)
{
	t_list		*env;
	t_member	**entries;

	env = *e;
	entries = malloc(ft_lstsize(env) + 1);
	if (!entries)
		return ;
	env = export_prepare_sort(entries, &env);
	if (env == NULL)
		return ;
	export_prepare_sort(entries, &env);
	free(entries);
}
