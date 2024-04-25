/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:56:53 by aboulore          #+#    #+#             */
/*   Updated: 2024/04/24 16:04:25 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_wddesc(void *word)
{
	t_wd_desc	*del;

	if (!word)
		return ;
	del = (t_wd_desc *)word;
	free(del->word);
	free(del);
}

void	free_before_id(t_list *inputs, size_t in_nb)
{
	size_t	i;
	t_list	*del;
	t_list	*tmp;
	t_list	*tmp2;

	i = 0;
	tmp = inputs;
	if (!tmp)
		return ;
	while (i < in_nb)
	{
		del = (t_list *)tmp->content;
		ft_lstclear(&del, &del_wddesc);
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
		i++;
	}
}

void	free_cmd_list(t_command *cmd)
{
	t_command	*tmp;
	int			i;
	
	while (cmd)
	{
		free(cmd->command);
		if (cmd->infile_name)
			free(cmd->infile_name);
		if (cmd->outfile_name)
			free(cmd->outfile_name);
		if (cmd->argv)
		{
			i = 0;
			while (cmd->argv[i])
			{
				free(cmd->argv[i]);
				i++;
			}
			free(cmd->argv);
		}
		tmp = cmd;
		cmd = cmd->pipe_right;
		free(tmp);
	}
}
