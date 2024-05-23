/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_superjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:19:29 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/23 14:07:56 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_superjoin(char **strs, char *sep)
{
	size_t	size;
	size_t	i;
	char	*str;

	size = ft_arrlen(strs);
	i = 0;
	if (sep)
		str = ft_calloc(sizeof(char), (ft_megalen(strs) + \
			ft_strlen(sep) * size + 1));
	else
		str = ft_calloc(sizeof(char), ft_megalen(strs) + 1);
	if (!str)
		return (NULL);
	while (i < size)
	{
		ft_strlcat(str, (const char *)strs[i], ft_strlen(str) \
			+ ft_strlen(strs[i]) + 1);
		if (sep)
			ft_strlcat(str, (const char *)strs[i], ft_strlen(str) \
				+ ft_strlen(sep) + 1);
		i++;
	}
	if (size == 0)
		return (NULL);
	return (str);
}
