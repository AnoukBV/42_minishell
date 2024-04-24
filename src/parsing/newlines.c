/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newlines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:53:28 by aboulore          #+#    #+#             */
/*   Updated: 2024/04/24 14:22:39 by aboulore         ###   ########.fr       */
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
	if (!inputs)
		ft_error();
	return (inputs);
}
