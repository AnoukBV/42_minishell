/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_esc_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 08:05:43 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/03 14:53:28 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	count_arrays(char const *s, char *c)
{
	int	i;
	int	len_split;
	t_esc	stat;

	i = 0;
	len_split = 0;
	stat.is_quoted = false;
	while (s[i])
	{
		check_quote(&stat, (char *)&s[i]);
		if ((!ft_strchr(c, s[i]) || (ft_strchr(c, s[i] && is_space_esc(stat, s[i]) == true ))) \
			&& ((ft_strchr(c, s[i + 1]) || s[i + 1] == 0) && is_space_esc(stat, s[i + 1]) == false))
			len_split++;
		i++;
	}
	return (len_split);
}

static char	**free_split(char **split, int len_split)
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

static char	**fill_split(char **split, char const *s, char *c, int len_split)
{
	int	j;
	int	i;
	int	len_array;
	int	start;
	t_esc	stat;

	i = 0;
	j = 0;
	stat.is_quoted = false;
	while (j < len_split)
	{
		len_array = 0;
		while ((ft_strchr(c, s[i]) && is_space_esc(stat, s[i]) == false) && s[i] != '\0')
		{
			check_quote(&stat, (char *)&s[i]);
			i++;
		}
		start = i;
		while ((!ft_strchr(c, s[i]) || (ft_strchr(c, s[i]) && is_space_esc(stat, s[i]) == true)) && s[i] != '\0')
		{
			check_quote(&stat, (char *)&s[i]);
			len_array++;
			i++;
		}
		split[j] = ft_substr(s, start, len_array);
		if (!split[j])
			split = free_split(split, len_split);
		j++;
	}
	split[j] = NULL;
	return (split);
}

char	**ft_esc_split(char *s, char *c)
{
	char	**split;
	char	*to_split;
	int		len_split;
	
	//printf("\n[ft_esc_split] char *s at beginning: BEG/%s/END\n", s);
	to_split = ft_strtrim(s, " \t");
	//if (*to_split == 0)
	//	return (0);
	//printf("\n[ft_esc_split] char *to_split after trim: BEG/%s/END\n", to_split);
	free(s);
	len_split = count_arrays(to_split, c);
	//printf("\n[ft_esc_split] len_split: %d\n", len_split);
	split = malloc(sizeof(char *) * (len_split + 1));
	if (split == NULL)
		return (NULL);
	split = fill_split(split, to_split, c, len_split);
	free(to_split);
	if (!split)
		split = free_split(split, len_split);
	return (split);
}

t_bool is_space_esc(t_esc stat, char c)
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