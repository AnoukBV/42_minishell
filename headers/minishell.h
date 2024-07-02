/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:11:16 by aboulore          #+#    #+#             */
/*   Updated: 2024/07/02 11:37:36 by aboulore         ###   ########.fr       */
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
# include "data.h"
# include "builtins.h"
# include "parsing.h"
# include "environment.h"
# include "errors.h"
# include "execution.h"
# include "signals.h"
# include "keys.h"
# include "heredoc.h"

# define MAX_HEREDOC 100000

char		*get_prompt(t_bool clear);
int			shell_prompt(t_list **env);
char		*get_prompt(t_bool clear);
void		clear_statics(void);

#endif
