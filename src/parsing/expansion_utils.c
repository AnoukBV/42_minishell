/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:07:52 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/29 09:27:50 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_after_expansion(char **tok, t_list **splitted_token)
{
	t_list	*tmp;
	char	*save;
	char	*new;

	tmp = *splitted_token;
	new = "\0";
	while (tmp)
	{
		save = ft_strdup(new);
	//	printf("\n[join_after_expansion] save(str to be added to the final str): %s\n", save);
		new = ft_strjoin(save, (char *)tmp->content);
	//	printf("\n[join_after_expansion] new(final str): %s\n", new);
		free(save);
		save = NULL;
		tmp = tmp->next;
	}
	if (*new == '\0')
		new = NULL;
	*tok = new;
}

void	init_tracker(t_exp **exp_status)
{
	*exp_status = malloc(sizeof(t_exp));
	if (!(*exp_status))
		return ;
	(*exp_status)->esc_status = malloc(sizeof(t_esc));
	if (!(*exp_status)->esc_status)
		return ;
	(*exp_status)->esc_status->is_quoted = false;
	(*exp_status)->is_exp_sim = false;
	(*exp_status)->is_exp_quo = false;
}
