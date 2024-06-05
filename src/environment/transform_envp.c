/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 23:50:46 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/05 10:08:07 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_key_value(t_member *m)
{
	char	*tmp;
	char	*final;

	if (!m)
		return (NULL);
	tmp = ft_strjoin(m->key, "=");
	final = ft_strjoin(tmp, m->value);
	free(tmp);
	return (final);
}

char	**transform_envp(t_list *env)
{
	t_list	*curr;
	char	**final;
	size_t	i;

	i = 0;
	if (!env)
		return (NULL);
	curr = env;
	final = ft_calloc(sizeof(char *), ft_lstsize(env) + 1);
	if (!final)
		malloc_error();
	while (curr)
	{
		final[i] = join_key_value(curr->content);
		curr = curr->next;
		i++;
	}
	final[i] = NULL;
	return (final);
}
