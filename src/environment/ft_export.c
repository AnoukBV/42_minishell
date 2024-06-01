/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:19:12 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/01 22:41:44 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	make_key(t_member **m, char *argv, int eq)
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
	return (0);
}

static int	make_value(t_member **m, char *argv, int eq)
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
	return (0);
	//export_expansion(room->value, env);
}

static int	add_member(char *argv, t_list *env, int eq)
{
	t_member	*room;
	char		*search;

	if (argv[eq - 1] == '+')
		search = ft_substr(argv, 0, eq - 1);
	else
		search = ft_substr(argv, 0, eq);
	if (argv[0] == '-' && ft_strlen(argv) > 1)
		return (ft_exp_option_mess(argv[1]));
	if (exp_check_err(search) == 1)
		return (ft_exp_err_mess(argv));
	room = env_find_tmemb(search, &env);
	if (!room)
	{
		room = create_table_member(NULL, NULL, false);
		ft_lstadd_back(&env, ft_lstnew(room));
	}
	free(search);
	if (make_key(&room, argv, eq) == 1 || make_value(&room, argv, eq) == 1)
		return (1);
	return (0);
}

int	ft_export(t_list **env, char **argv)
{
	int			*eq;
	size_t		i;
	int		exit;

	i = 0;
	exit = 1;
	if (argv == NULL)
		return (exit);
	if (ft_arrlen(argv) == 1)
		exit = print_env(env, EXPORT);
	else if (argv[1][0] == '\0')
		exit = ft_exp_err_mess("\0");
	else
	{
		eq = split_key_value(argv);
		while (i < ft_arrlen(&argv[1]))
		{
			//ft_putstr_fd(argv[i + 1], 1);
			//ft_putchar_fd('\n', 1);
			exit = add_member(argv[i + 1], *env, eq[i]);
			//ft_putnbr_fd(exit, 1);
			//ft_putchar_fd('\n', 1);
			i++;
		}
		free(eq);
	}
	return (exit);
}
