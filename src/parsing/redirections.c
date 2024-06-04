/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 07:59:46 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/04 16:35:30 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assignate_flags_dir(int tok_flags, int *open_flags, int *fd)
{
	if (tok_flags == T_RED_OUT)
	{
		*open_flags = O_WRONLY | O_TRUNC | O_CREAT;
		*fd = 1;
	}
	else if (tok_flags == T_RED_IN)
	{
		*open_flags = O_RDONLY;
		*fd = 0;
	}
	else if (tok_flags == T_APP_IN)
	{
		*open_flags = T_APP_IN;
		*fd = 0;
	}
	else if (tok_flags - 100 == T_APP_IN)
	{
		*open_flags = T_APP_IN + 100;
		*fd = 0;
	}
	else if (tok_flags == T_APP_OUT)
	{
		*open_flags = O_WRONLY | O_APPEND | O_CREAT;
		*fd = 1;
	}
}
