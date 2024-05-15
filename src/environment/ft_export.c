/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:19:12 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/15 10:42:38 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	packed_env(void)
{
	ft_putstr_fd("minishell: environment is full\n", 1);
}

void	make_key(t_member **m, char *argv, int eq)
{
	t_member	*room;

	room = *m;
	if (!room->key)
	{
		if (argv[eq - 1] == '+')
			room->key = ft_substr(argv, 0, eq - 1);
		else
			room->key = ft_substr(argv, 0, eq);
	}
	else if (room->value && argv[eq - 1] != '+')
	{
		free(room->value);
		room->value = NULL;
	}
}

void	make_value(t_member **m, char *argv, int eq, t_hashtable *env)
{
	char		*search;
	char		*save;
	t_member	*room;

	room = *m;
	if (eq + 1 < (int)ft_strlen(argv))
	{
	  	if (argv[eq - 1] == '+')
		{
		  	save = room->value;
		  	search = ft_substr(&argv[eq + 1], 0, \
				ft_strlen((&argv[eq]) - 1));
			room->value = ft_strjoin(save, search);
			free(search);
			free(save);
		}
		else
			room->value = ft_substr(&argv[eq + 1], 0, \
				ft_strlen((&argv[eq]) - 1));
	}
	(void)env;
	//export_expansion(room->value, env);
}

void	add_member(char *argv, t_hashtable *env, size_t size, int eq)
{
	t_member	*room;
	char		*search;

	if (argv[eq - 1] == '+')
		search = ft_substr(argv, 0, eq - 1);
	else
		search = ft_substr(argv, 0, eq);
	exp_check_err(search);
	room = env_find_tmemb(env->member, search, size);
	if (!room)
		room = env_fetch_member(env->member, size);
	if (!room)
	{
		packed_env();
		return ;
	}
	free(search);
	make_key(&room, argv, eq);
	make_value(&room, argv, eq, env);
}

void	ft_export(t_pipeline *p, t_command *cmd)
{
	t_hashtable	*env;
	char		**argv;
	int			*eq;
	size_t		i;

	i = 0;
	env = *p->hash_env;
	argv = cmd->argv;
	if (cmd->argv == NULL)
		return ;
	if (cmd->is_argv == true && ft_arrlen(argv) == 1)
	{
		print_env(&env, EXPORT);
		return ;
	}
	eq = split_key_value(argv);
	while (i < ft_arrlen(&argv[1]))
	{
		add_member(argv[i + 1], env, env->size, eq[i]);
		i++;
	}
	free(eq);
}
