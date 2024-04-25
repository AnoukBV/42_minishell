/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_superjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:19:29 by aboulore          #+#    #+#             */
/*   Updated: 2024/04/24 18:07:10 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_arrlen(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		i++;
	}
	return (i);
}

static size_t	ft_megalen(char **strs)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
			j++;
		k += j;
		i++;
	}
	return (k);
}

char	*ft_superjoin(char **strs, char *sep)
{
	size_t	size;
	size_t	i;
	char	*str;

	size = ft_arrlen(strs);
	i = 0;
	if (sep)
		str = ft_calloc(sizeof(char), (ft_megalen(strs) + ft_strlen(sep) * size + 1));
	else
		str = ft_calloc(sizeof(char), ft_megalen(strs) + 1);
	if (!str)
		return (NULL);
	while (i < size)
	{
		ft_strlcat(str, (const char *)strs[i], ft_strlen(str) + ft_strlen(strs[i]) + 1);
		if (sep)
			ft_strlcat(str, (const char *)strs[i], ft_strlen(str) + ft_strlen(sep) + 1);
		i++;
	}
	return (str);
}
