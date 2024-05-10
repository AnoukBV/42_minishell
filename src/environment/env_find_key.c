/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:59:25 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/10 17:00:26 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_find_key(t_member **member, char *key, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (member[i]->key && !ft_strncmp(member[i]->key, key, ft_strlen(key)))
			return (member[i]->value);
		i++;
	}
	return ("\0");
}
