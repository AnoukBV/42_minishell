/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:11:16 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/02 08:50:49 by aboulore         ###   ########.fr       */
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
}	t_esc;

typedef struct s_wd_desc
{
	char	*word;
	int		flags;
}	t_wd_desc;

typedef struct	s_redir_list
{
	int						fd_to_redirect;
	char					*target_filename;
	int						open_flags; // open() flags used for target file
	//int						type;	//ARTHUR : MODIF ICI
	struct s_redir_list		*next;
}	t_redir_list;

typedef struct	s_command
{
	int					flags;
	t_list				*cmd; //ARTHUR : MODIF ICI
	char				**argv; // name (+ path) of the command
	char				*command; // name (+ path) of the command
	t_redir_list		*redir_list;
	int					pipe_left[2];
	int					pipe_right[2];
	struct s_command		*next;
	struct s_command		*prev;
}	t_command;

// parsing

void			parsing(char *str, t_list **inputs);
char			**newlines(char *str, size_t *input_nb);
void			break_into_words(t_list **inputs, char *inputs_array);
void			word_or_operator(t_list **inputs);
void			check_quote(t_esc *esc_status, char *str);
t_wd_desc		*new_wd_desc(int flags, char *word);
void			divide(t_list **inputs, t_btree **tree);
void			addback_redir(t_redir_list **redir, t_redir_list *new);
t_bool			is_redir(t_list *inputs);
t_btree			*malloc_bst(void);
t_command		*init_cmd(void);
t_bool			check_validity_parenthesis(t_list *list);
void			new_branch(t_wd_desc *tok, t_btree \
				*holder, t_btree **tree);
void			is_between_p(t_list **inputs, t_btree **tree);
void			assignate_flags_dir(int tok_flags, \
				int *open_flags, int *fd);
void			undefault_fd_tok(t_list **list, t_wd_desc **redir);

//environment

void	print_env(t_hashtable *env, int key);
void	set_hashtable(char **envp, t_hashtable **env);

//utils

void	ft_error(void);
void	free_before_id(t_list *inputs, size_t in_nb);
void	free_binary_tree(t_btree *tree);
void	del_wddesc(void *word);

//side

void	print_2d_array(char **str);
void	print_unidentified_tokens(t_list *inputs);
void	print_divided_cmds(t_btree *cmds, size_t levels);
int		Size(t_btree *root);

// signals.c
void	set_rl_signals(void);

#endif
