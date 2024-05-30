/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:35:34 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/27 15:55:04 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_table(char **envp, t_list **env)
{
  	size_t	i;
	t_member	*new;

	while (*envp)
	{
		i = 0;
		while ((*envp)[i] != '=' && (*envp)[i])
			i++;
		if ((*envp)[i] == '=')
		{
			new = create_table_member(ft_substr(*envp, 0, i), \
				ft_substr(*envp, i + 1, ft_strlen(*envp) - i - 1), true);
			ft_lstadd_back(env, ft_lstnew(new));
		}
		envp++;
	}
}

t_member	*create_table_member(char *key, char *value, t_bool is_og)
{
	t_member	*new;

	new = malloc(sizeof(t_member));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->is_og = is_og;
	return (new);
}

void	set_hashtable(char **envp, t_list **env)
{
	// size_t	size;

	// size = ft_arrlen(envp);
	/*if (size == 0)
	{
		create_table(env, 1024);	//securiser
		return ;
	}*/
	fill_table(envp, env);
	//print_env(*env, ENV);
}

void	del_member(void *content)
{
	t_member	*del;
	
	del = (t_member *)content;
	if (!del)
		return ;
	if (del->key)
		free(del->key);
	if (del->value)
		free(del->value);
	free(del);
}
