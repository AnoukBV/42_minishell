/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newlines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:53:28 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/05 11:06:50 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_inputs(char *str)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 1;
	while (str[i])
	{
		if (str[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

char	**newlines(char *str, size_t *input_nb)
{
	char	**inputs;

	if (!str)
		return (NULL);
	*input_nb = count_inputs(str);
	inputs = ft_split(str, '\n');
	//if (!inputs)
	//	ft_error();
	return (inputs);
}

t_wd_desc	*new_wd_desc(int flags, char *word)
{
	t_wd_desc	*new;

	new = malloc(sizeof(t_wd_desc));
	if (!new)
		malloc_error();
	new->flags = flags;
	new->word = word;
	return (new);
}

t_bool	is_space_esc(t_esc stat, char c)
{
	if (!c)
		return (false);
	else if (!ft_strchr(" \t", c))
		return (true);
	else if (stat.is_quoted == true)
		return (true);
	else if (stat.is_quoted == false)
		return (false);
	return (false);
}

char	**free_split(char **split, int len_split)
{
	int	i;

	i = 0;
	while (i < len_split)
	{
		free(split[i]);
		i++;
	}
	split = NULL;
	return (split);
}
