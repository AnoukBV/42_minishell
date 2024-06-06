/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:15:37 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/06 10:15:59 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*new_limiter(size_t old, char *token, int ret)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_calloc(sizeof(char), (int)old - ret + 1);
	if (!new)
		malloc_error();
	while (token[i])
	{
		if (token[i] == '$' && token[i + 1] && (token[i + 1] == '\'' \
			|| token[i + 1] == '"'))
			i++;
		new[ft_strlen(new)] = token[i];
		i++;
	}
	new[ft_strlen(new)] = '\0';
	return (new);
}

int	heredoc_expansion(char **token)
{
	int		i;
	int		size;
	char	*str;

	i = 0;
	size = 0;
	str = *token;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && (str[i + 1] == '\'' \
			|| str[i + 1] == '"'))
			size++;
		i++;
	}
	if (size == 0)
		return (0);
	*token = new_limiter(ft_strlen(*token), *token, size);
	free(str);
	return (0);
}
