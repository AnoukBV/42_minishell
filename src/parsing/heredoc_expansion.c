/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:15:37 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/18 15:08:30 by abernade         ###   ########.fr       */
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

static char	*retrieve_dollar(char *str)
{
	int		i;
	int		size;
	char	*new;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && (str[i + 1] == '\'' \
			|| str[i + 1] == '"'))
			size++;
		i++;
	}
	if (size == 0)
		return (0);
	new = new_limiter(ft_strlen(str), str, size);
	free(str);
	return (new);
}

int	heredoc_expansion(char **token)
{
	*token = retrieve_dollar(*token);
	return (0);
}

char	*get_next_heredoc(char *name)
{
	char	*for_exp;
	char	*tmp;
	char	*save;
	int		fd;

	fd = open(name, O_RDONLY);
	for_exp = ft_strdup("");
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		save = for_exp;
		for_exp = ft_strjoin(save, tmp);
		free(save);
		free(tmp);
	}
	free(tmp);
	close(fd);
	return (for_exp);
}
