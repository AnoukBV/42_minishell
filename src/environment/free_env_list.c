/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:47:48 by abernade          #+#    #+#             */
/*   Updated: 2024/06/26 07:45:10 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_member(void *elem)
{
	t_member	*member;

	member = (t_member *)elem;
	free(member->key);
	free(member->value);
	free(member);
}

void	free_env_list(t_list **env_list)
{
	ft_lstclear(env_list, &free_env_member);
}
