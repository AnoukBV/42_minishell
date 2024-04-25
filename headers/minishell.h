/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:11:16 by aboulore          #+#    #+#             */
/*   Updated: 2024/04/25 18:45:22 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <termios.h>
# include <errno.h>
# include "libft.h"
# include "keys.h"
# include "environment.h"

typedef enum e_bool { false, true }	t_bool;

typedef struct s_esc
{
	t_bool	is_quoted;
	t_bool	is_simplequote;
	//t_bool	is_aquote;
	//t_bool	is_closing;
}	t_esc;

typedef struct s_wd_desc
{
	char	*word;
	int		flags;
}	t_wd_desc;

// parsing

void		parsing(char *str, t_list **inputs);
char		**newlines(char *str, size_t *input_nb);
void		break_into_words(t_list **inputs, char *inputs_array);
void		word_or_operator(t_list **inputs);
void		check_quote(t_esc *esc_status, char *str);
t_wd_desc	*new_wd_desc(int flags, char *word);
void		divide(t_list **inputs, t_list **new);

//utils

void	ft_error(void);
void	free_before_id(t_list *inputs, size_t in_nb);
void	del_wddesc(void *word);

//side

void	print_2d_array(char **str);
void	print_unidentified_tokens(t_list *inputs);
void	print_divided_cmds(t_list *cmds);

// signals.c
void	set_rl_signals(void);

#endif
