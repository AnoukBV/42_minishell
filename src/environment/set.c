/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:35:34 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/06 12:55:51 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_table(char **envp, t_list **env)
{
	size_t		i;
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
		malloc_error();
	new->key = key;
	new->value = value;
	new->is_og = is_og;
	return (new);
}

void	increment_shlvl(t_member **shlvl)
{
	int	lvl;

	if (!shlvl || !(*shlvl))
		return ;
	lvl = ft_atoi((*shlvl)->value);
	lvl = lvl + 1;
	free((*shlvl)->value);
	(*shlvl)->value = ft_itoa(lvl);
}

void	set_hashtable(char **envp, t_list **env)
{
	char		**envi;
	char		buf[PATH_MAX];
	t_member	*shlvl;

	if (!envp[0])
	{
		envi = ft_calloc(sizeof(char *), 4);
		if (!envi)
			malloc_error();
		getcwd(buf, PATH_MAX);
		envi[0] = ft_strjoin("PWD=", (const char *)buf);
		envi[1] = ft_strdup("SHLVL=1");
		envi[2] = ft_strdup("PATH=/usr/bin");
		envi[3] = NULL;
		fill_table(envi, env);
		free_array_2d(envi);
	}
	else
		fill_table(envp, env);
	shlvl = env_find_tmemb("SHLVL", env);
	increment_shlvl(&shlvl);
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
