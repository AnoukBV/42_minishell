/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 08:14:48 by abernade          #+#    #+#             */
/*   Updated: 2024/06/06 09:03:35 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_heredoc_name(void)
{
	char	*filename;
	char	*nb;
	int		i;

	i = 0;
	nb = ft_itoa(i);
	filename = ft_strjoin("heredoc", nb);
	free(nb);
	while (!access(filename, F_OK) && i < MAX_HEREDOC)
	{
		i++;
		free(filename);
		nb = ft_itoa(i);
		filename = ft_strjoin("heredoc", nb);
		free(nb);
	}
	if (i == MAX_HEREDOC)
	{
		ft_putstr_fd("heredoc error\n", 2);
		exit(1);
	}
	return(filename);
}
