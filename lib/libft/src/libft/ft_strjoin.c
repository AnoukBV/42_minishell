/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 07:54:17 by aboulore          #+#    #+#             */
/*   Updated: 2024/01/27 14:12:41 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sfinal;

	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	sfinal = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (sfinal == NULL)
		return (NULL);
	sfinal[0] = '\0';
	ft_strlcat(sfinal, s1, ft_strlen(s1) + 1);
	ft_strlcat(sfinal, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (sfinal);
}
