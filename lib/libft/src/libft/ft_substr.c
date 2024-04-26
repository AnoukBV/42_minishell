/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:51:12 by aboulore          #+#    #+#             */
/*   Updated: 2024/04/26 07:18:49 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (!s)
		return (0);
	if (len > 0 && start < ft_strlen(s))
	{
		if (ft_strlen(s) - start >= len)
			str = malloc(sizeof(char) * len + 1);
		else
			str = malloc(sizeof(char) * \
				(ft_strlen(s) - start) + 1);
		if (str == NULL)
			return (NULL);
		ft_strlcpy(str, &s[start], len + 1);
		return (str);
	}
	return (ft_calloc(1, 1));
}
