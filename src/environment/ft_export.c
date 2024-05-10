/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:19:12 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/10 16:29:28 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static void	export_print(t_hashtable *env)

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
			member[i] = malloc(sizeof(t_member));
			return (member[i]);
		}
		i++;
	}
	return (NULL);
}

void	ft_export(t_pipeline *pipeline, t_command *cmd)
{
	t_member	*room;
	char		**argv;
	t_hashtable	*env;
	int			*eq;
	size_t		i;

	i = 0;
	//(void)pipeline;
	env = *pipeline->hash_env;
	if (cmd->argv == NULL)
		return ;
	argv = cmd->argv;
	if (cmd->is_argv == true && ft_arrlen(argv) == 1)
	{
	  //print_env(cmd->env, EXPORT);
		return ;
	}
	eq = split_key_value(argv);
	while (i < ft_arrlen(&argv[1]))
	{
		room = env_fetch_member(env->member, env->size);
		//if (!room)
			//ici secu si PLUS DE PLACE
		room->key = ft_substr(argv[i + 1], 0, eq[i]);
		if (eq[i] + 1 < (int)ft_strlen(argv[i + 1]))
			room->value = ft_substr(&argv[i + 1][eq[i] + 1], 0, \
				ft_strlen((&argv[i + 1][eq[i]]) - 1));
		i++;
	}
	free(eq);
}

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
