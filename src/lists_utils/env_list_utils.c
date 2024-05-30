/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:23:49 by abernade          #+#    #+#             */
/*   Updated: 2024/05/30 15:46:54 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	update_env_element(t_list **env_lst, char *key, char *value)
{
	char		*key_dup;
	t_list		*new;
	t_list		*lst;
	t_member	*env_elem;

	lst = *env_lst;
	while (lst)
	{
		env_elem = lst->content;
		if (!ft_strncmp(env_elem->key, key, ft_strlen(key)))
		{
			if (env_elem->value)
				free(env_elem->value);
			env_elem->value = value;
			return ;
		}
		lst = lst->next;
	}
	key_dup = ft_strdup(key);
	env_elem = create_table_member(key_dup, value, false);
	new = ft_lstnew(env_elem);
	new->next = NULL;
	ft_lstadd_back(env_lst, new);
}
