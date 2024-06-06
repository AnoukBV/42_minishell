/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 08:16:05 by abernade          #+#    #+#             */
/*   Updated: 2024/06/06 09:35:09 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

char	*get_heredoc_name(void);
char	*new_heredoc(const char *delimiter, t_list **envp, t_command **cmd);
void		delete_heredoc(char *filename, t_list *env);

#endif