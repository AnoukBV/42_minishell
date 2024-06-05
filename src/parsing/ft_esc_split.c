/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_esc_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 08:05:43 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/05 11:08:43 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_skip_sep(char const *s, char *c, t_esc *stat, int *i)
{
	int	ii;

	ii = *i;
	while ((ft_strchr(c, s[ii]) && is_space_esc(*stat, s[ii]) \
		== false) && s[ii] != '\0')
	{
		check_quote(stat, (char *)&s[ii]);
		ii++;
	}
	*i = ii;
}

static int	split_len_array(int *i, char const *s, char *c, t_esc *stat)
{
	int	len_array;

	len_array = 0;
	while ((!ft_strchr(c, s[*i]) || (ft_strchr(c, s[*i]) \
		&& is_space_esc(*stat, s[*i]) == true)) && s[*i] != '\0')
	{
		check_quote(stat, (char *)&s[*i]);
		len_array++;
		*i += 1;
	}
	return (len_array);
}

static char	**fill_split(char **split, char \
	const *s, char *c, int len_split)
{
	int		j;
	int		i;
	int		start;
	t_esc	stat;

	i = 0;
	j = 0;
	stat.is_quoted = false;
	while (j < len_split)
	{
		split_skip_sep(s, c, &stat, &i);
		start = i;
		split[j] = ft_substr(s, start, split_len_array(&i, s, c, &stat));
		if (!split[j])
			split = free_split(split, len_split);
		j++;
	}
	split[j] = NULL;
	return (split);
}

static int	count_arrays(char const *s, char *c)
{
	int		i;
	int		len_split;
	t_esc	stat;

	i = 0;
	len_split = 0;
	stat.is_quoted = false;
	while (s[i])
	{
		check_quote(&stat, (char *)&s[i]);
		if ((!ft_strchr(c, s[i]) || (ft_strchr(c, s[i] && \
			is_space_esc(stat, s[i]) == true))) \
			&& ((ft_strchr(c, s[i + 1]) || s[i + 1] == 0) && \
			is_space_esc(stat, s[i + 1]) == false))
			len_split++;
		i++;
	}
	return (len_split);
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
		malloc_error();
	split = fill_split(split, to_split, c, len_split);
	free(to_split);
	if (!split)
		split = free_split(split, len_split);
	return (split);
}
