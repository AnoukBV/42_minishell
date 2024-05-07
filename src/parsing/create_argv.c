/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:37:56 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/07 20:08:16 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**from_list_to_array(t_list *list, size_t size)
{
	t_list	*tmp;
	t_wd_desc	*tok;
	size_t	i;
	char	**final;

	i = 0;
	tmp = list;
	final = ft_calloc(sizeof(char *), size + 1);
	if (!list || !final)
		return (NULL);
	while (i < size)
	{	
		tok = (t_wd_desc *)tmp->content;
		final[i] = ft_strdup(tok->word);
		tmp = tmp->next;
		i++;
	}
	return (final);
}

void	create_argv(void *item)
{
	//si void pointe vers t_list : join, free, return le truc
	t_command	*cmd;
	char		**argv;

	cmd = (t_command *)item;
	if (cmd->is_argv == true)
	{
		argv = from_list_to_array((t_list *)cmd->argv, \
			ft_lstsize((t_list *)cmd->argv));
		ft_lstclear((t_list **)&cmd->argv, &del_wddesc);
		cmd->argv = argv;
	}
	//else
	//si pointe vers autre chose (commente pr l'instant) --> recursivite et on applique 
	//meme chose avec une sort de lst map pr t_cmd
}
