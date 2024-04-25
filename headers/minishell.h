/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:11:16 by aboulore          #+#    #+#             */
/*   Updated: 2024/04/25 19:21:21 by abernade         ###   ########.fr       */
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
# include "libft.h"
# include "keys.h"

int	g_status;

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

typedef struct	s_redir_list
{
	int						fd_to_redirect;
	char					*target_filename;
	int						open_flags; // open() flags used for target file
	struct s_redirection	*next;
}	t_redir_list;

typedef struct	s_command
{
	char				**argv; // list of command argument
	char				*command; // name (+ path) of the command
	t_redir_list		*redir_list;
	int					pipe_left[2];
	int					pipe_right[2];
	struct s_command	*next;
	struct s_command	*prev;
} t_command;

/*
*	A list of file descriptors to close before calling execve()
*/
typedef	struct	s_fd_list
{
	int			fd;
	t_fd_list	*next;
}	t_fd_list;

typedef struct	s_pipeline
{
	t_command	*cmd_list;
	t_fd_list	*fd_list;
	char		**envp;
}	t_pipeline;

// parsing

size_t	parsing(char *str, t_list **inputs);
char	**newlines(char *str, size_t *input_nb);
void	break_into_words(t_list **inputs, char **inputs_array, size_t input_nb);
//void	word_or_operator(

/*
*	Error functions
*/
void	ft_error(void);
void	pipe_error(t_pipeline *pipeline);
void	redirection_error(t_command *cmd_lst);
void	malloc_error(void);

//utils
void	free_before_id(t_list *inputs, size_t in_nb);
void	del_wddesc(void *word);

//side

void	print_2d_array(char **str);
void	print_unidentified_tokens(size_t input_nb, t_list *inputs);

/*
*	Signal control functions, switching between readline and command execution states
*/

// Sets signal handlers to behave like bash when readline() is being executed
void	set_rl_signals(void);

/*
*	Test functions /!\ TO BE DELETED /!\
*/
t_command	*create_dummy();

/*
*	Memory utils
*/
void	free_cmd_list(t_command *cmd);

/*
*	Executor functions
*/
void	execute_pipeline(t_pipeline *pipeline);


	/*
	*	Manage t_pipeline structures
	*/

/*
*	Creates and initialize t_pipeline structure
*	Creates all pipes in its command list `cmd_lst`
*	No redirection is done at this time
*/
t_pipeline	*init_pipeline(t_command *cmd_lst, char **envp);
void		destroy_pipeline(t_pipeline *pipeline);
void		destroy_cmd_list(t_command *cmd)


	/*
	*	Manage t_fd_list structures
	*/

/*
*	Removes file descriptor `fd` from the list
*	Returns 0 on success, or -1 if `fd` was not found in the list
*/
int		remove_fd(int fd, t_fd_list **fds);

void	close_fd_list(t_fd_list **fds);
void	add_fd(int fd, t_fd_list **fds);

#endif
