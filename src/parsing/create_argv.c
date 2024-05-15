/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:37:56 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/15 13:05:06 by aboulore         ###   ########.fr       */
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

char	*find_path(char *cmd_name, t_hashtable **env)
{
	size_t	i;
	char	*str_path;
	char	**all_paths;
	char	*tmp;
	char	*path_cmd;

	i = 0;
	if (access(cmd_name, F_OK) == 0 || \
		access(cmd_name, X_OK) == 0)
		return (ft_strdup(cmd_name));
	str_path = env_find_key((*env)->member, "PATH", (*env)->size);
	if (!str_path)
		return (NULL);
	all_paths = ft_split(str_path, ':');
	while (all_paths[i] != NULL)
	{
		tmp = ft_strjoin(all_paths[i], "/");
		path_cmd = ft_strjoin(tmp, cmd_name);
		free(tmp);
		if (access(path_cmd, F_OK) == 0 || access(path_cmd, X_OK) == 0)
		{	
		  	free_array_2d(all_paths);
			return (path_cmd);
		}
		free(path_cmd);
		path_cmd = NULL;
		i++;
	}
	return (ft_strdup(cmd_name));
}

void	create_argv(void *item)
{
	//si void pointe vers t_list : join, free, return le truc
	t_command	*cmd;
	char		**argv;

	cmd = (t_command *)item;
	if (cmd->is_argv == true && cmd->flags == 0)
	{
		argv = from_list_to_array((t_list *)cmd->argv, \
			ft_lstsize((t_list *)cmd->argv));
		ft_lstclear((t_list **)&cmd->argv, &del_wddesc);
		cmd->argv = argv;
		cmd->command = ft_strdup(argv[0]);
	}
	//else
	//si pointe vers autre chose (commente pr l'instant) --> recursivite et on applique 
	//meme chose avec une sort de lst map pr t_cmd
}
