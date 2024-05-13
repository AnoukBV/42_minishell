/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:11:16 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/13 16:19:29 by abernade         ###   ########.fr       */
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
# include "libft.h"
# include "keys.h"
# include "environment.h"

typedef enum e_bool { false, true }	t_bool;

typedef struct s_esc
{
	t_bool	is_quoted;
	t_bool	is_simplequote;
}	t_esc;

typedef struct s_exp
{
	t_esc	*esc_status;
	t_bool	is_exp_sim;
	t_bool	is_exp_quo;
}	t_exp;

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
	struct s_redir_list		*next;
}	t_redir_list;

/*
typedef struct	s_command
{
	char				**argv; // list of command argument
	char				*command; // name (+ path) of the command
	t_redir_list		*redir_list;
	int					pipe_left[2];
	int					pipe_right[2];
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;
*/
// Pour anouk pour plus tard
typedef struct	s_command
{
	int					flags;
	t_bool				is_argv;
	void				*argv;
	char				*command; // name (+ path) of the command
	t_redir_list		*redir_list;
	int					pipe_left[2];
	int					pipe_right[2];
	t_hashtable			**env;
	struct s_command		*next;
	struct s_command		*prev;
}	t_command;

/*
*	A list of file descriptors to close before calling execve()
*/
typedef	struct	s_fd_list
{
	int					fd;
	struct s_fd_list	*next;
}	t_fd_list;

/*
*	A list of child processes pid
*/
typedef struct	s_pid_list
{
	int					pid;
	struct s_pid_list	*next;
}	t_pid_list;

typedef struct	s_pipeline
{
	t_command	*cmd_list;
	t_fd_list	*fd_list;
	t_pid_list	*pid_list;
	// char		**envp;
	t_hashtable	*envp;
}	t_pipeline;

// parsing

t_pipeline		*parsing(char *str, t_list **inputs, t_hashtable *env);
char			**newlines(char *str, size_t *input_nb);
void			break_into_words(t_list **inputs, char *inputs_array);
void			word_or_operator(t_list **inputs);
void			check_quote(t_esc *esc_status, char *str);
t_wd_desc		*new_wd_desc(int flags, char *word);
void			divide(t_list **inputs, t_btree **tree, t_hashtable **env);
void			addback_redir(t_redir_list **redir, t_redir_list *new);
t_bool			is_redir(t_list *inputs);
t_btree			*init_bst(t_hashtable **env);
t_command		*init_cmd(t_hashtable **env);
t_bool			check_validity_parenthesis(t_list *list);
void			new_branch(t_wd_desc *tok, t_btree \
				*holder, t_btree **tree);
void			is_between_p(t_list **inputs, t_btree **tree, t_hashtable **env);
void			assignate_flags_dir(int tok_flags, \
				int *open_flags, int *fd);
void			undefault_fd_tok(t_list **list, t_wd_desc **redir);
void			check_quote_bis(t_esc *esc_status, char *str);
void			check_quote(t_esc *esc_status, char *str);
void			expansion(void *item);
t_bool			check_expansion(t_exp **expansion, char *str);
char			*expand(char *str, t_hashtable **env, size_t size);
void			inspect_token(char **str, t_hashtable **env);
void			join_after_expansion(char **tok, t_list **splitted_token);
void			create_argv(void *item);
void			fill_pipeline(t_pipeline **pipeline, t_btree *tree, t_hashtable *env);

/*
*	Error functions
*/
void	ft_error(void);
void	pipe_error(t_pipeline *pipeline);
void	redirection_error(t_command *cmd_lst);
void	malloc_error(void);
void	fork_error(t_pipeline *pipeline);
void	dup2_error(void);
void	open_error(char *filename);
void	check_execve_error(char *pathname, t_pipeline *pipeline);

//side

void	print_2d_array(char **str);
void	print_unidentified_tokens(t_list *inputs);
void	print_divided_cmds(t_btree *cmds, size_t levels);
int		Size(t_btree *root);
void	print_divided_cmds_array(t_btree *cmds, size_t levels);
void	print_pipeline(t_pipeline *pipeline);

	/*
	*	Signal control functions, switching between readline and command execution states
	*/

// Sets signal handlers to behave like bash when readline() is being executed
void	set_rl_signals(void);
// Restores default signal behavior
void	signals_default(void);

//	Signal handlers
void	rl_signals_handler(int sig);

/*
*	Test functions /!\ TO BE DELETED /!\
*/
t_pipeline	*dummydata(char **envp);

/*
*	Memory utils
*/
//void	free_cmd_list(t_command *cmd); //JE COMPRENDS PAS QD EST C QU'ON UTILISE CA
void	free_before_id(t_list *inputs, size_t in_nb);
void	del_wddesc(void *word);

/*
*	Executor functions
*/
void	execute_pipeline(t_pipeline *pipeline);


	/*
	*	Manage t_pipeline structures
	*/

/*
*	Creates and initialize t_pipeline structure
*	Creates all pipes in its command list
*	No redirection is done at this time
*/
t_pipeline	*init_pipeline(t_command *cmd_lst, char **env);
void		prepare_pipeline(t_pipeline *pipeline);

void		destroy_pipeline(t_pipeline *pipeline);

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

	/*
	*	Manage t_pid_list structures
	*/
void	add_pid(int pid, t_pid_list **pid_list);
void	remove_pid(int pid, t_pid_list **pid_list);

void	wait_all_pid(t_pid_list **pid_list);

/*
*	Execution utils
*/
t_bool	is_builtin(char *cmd_name);
int		get_status(int status);
char	*get_bin_path(t_hashtable *env, char *name);

//t_command utils

t_command	*command_last(t_command *command);
void		command_addback(t_command **list, t_command *new);
void		destroy_cmd_list(t_command **cmd);
void		destroy_cmd_one(t_command *cmd);

void	destroy_redir_list(t_redir_list **redir_list);

//NV A REMETTRE Dasn autre .h  apres mise en ordre du point h
//
void	set_hashtable(char **envp, t_hashtable **env);
void	delmemb_env(t_member *member);
char	*env_find_key(t_member **member, char *key, int size);
void	free_env(t_hashtable *env);
void	init_tracker(t_exp **exp_status);
char	**transform_envp(t_hashtable *env);
void	print_env(t_hashtable *env, int key);
#endif
