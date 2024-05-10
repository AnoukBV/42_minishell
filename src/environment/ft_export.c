/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:19:12 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/10 17:00:19 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_point(char *str)
{
	int	eq;

	eq = 0;
	while (str[eq] != '=')
		eq++;
	return (eq);
}

int	*split_key_value(char **argv)
{
	size_t	i;
	int		*eq;

	i = 1;
	eq = malloc(sizeof(int) * ft_arrlen(&argv[i]));
	if (!eq)
		return (NULL);
	while (argv[i])
	{
		//if (argv[i][0] == '=')
			//-bash: export: `=blabla': not a valid identifier, mais pas quitter, si des args sont valides on s'n occupe
		eq[i - 1] = split_point(argv[i]);
		i++;
	}
	return (eq);
}

t_member	*env_fetch_member(t_member **member, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (!member[i])
		{
			member[i] = ft_calloc(sizeof(t_member), 1);
			return (member[i]);
		}
		i++;
	}
	return (NULL);
}

void	add_member(char *argv, t_member **member, size_t size, int eq)
{
	t_member	*room;

	room = env_fetch_member(member, size);
	//if (!room)
		//ici secu si PLUS DE PLACE
	room->key = ft_substr(argv, 0, eq);
	if (eq + 1 < (int)ft_strlen(argv))
		room->value = ft_substr(&argv[eq + 1], 0, \
			ft_strlen((&argv[eq]) - 1));
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
	//if (cmd->is_argv == true && ft_arrlen(argv) == 1)
	  //print_env(cmd->env, EXPORT);
	eq = split_key_value(argv);
	while (i < ft_arrlen(&argv[1]))
	{
		add_member(argv[i + 1], env->member, env->size, eq[i]);
		i++;
	}
	free(eq);
}
