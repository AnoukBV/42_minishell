/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:11:16 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/06 15:03:56 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <termios.h>
# include <errno.h>
# include <sys/wait.h>
# include <linux/limits.h>
# include <limits.h>
# include <sys/stat.h>
# include "libft.h"
# include <data.h>
# include "builtins.h"
# include "parsing.h"
# include "environment.h"
# include "errors.h"
# include "execution.h"
# include "signals.h"
# include "keys.h"
# include <heredoc.h>

#define MAX_HEREDOC 10000

//side TO BE DELETED
void		print_2d_array(char **str);
void		print_unidentified_tokens(t_list *inputs);
void		print_divided_cmds(t_btree *cmds, size_t levels);
int			Size(t_btree *root);
void		print_divided_cmds_array(t_btree *cmds, size_t levels);
void		print_pipeline(t_pipeline *pipeline);
char		*get_prompt(t_bool clear);
void		shell_prompt(t_list **env);
char		*get_prompt(t_bool clear);
void		clear_statics(void);

#endif
