/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:55:21 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/09 17:07:43 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*s_dup;

	s_dup = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (s_dup == NULL)
		return (NULL);
	ft_strlcpy(s_dup, s, ((size_t)ft_strlen(s) + 1));
	return (s_dup);
}
