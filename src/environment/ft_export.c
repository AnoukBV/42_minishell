/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:19:12 by aboulore          #+#    #+#             */
/*   Updated: 2024/04/26 11:29:26 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_print(t_hashtable *env)

void	ft_export(t_hashtable *env, char *str)
{
	if (str == NULL)
		export_print(env);
	else
		return ;
}
