/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:11:16 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/05 07:59:55 by abernade         ###   ########.fr       */
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

typedef enum e_bool { false, true }	t_bool;
# include "environment.h"

typedef struct s_esc
{
	t_bool	is_quoted;
	t_bool	is_simplequote;
	t_bool	unclosed;
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

typedef struct	s_command
{
	int					flags;
	t_bool				is_argv;
	void				*argv;
	char				*command; // name (+ path) of the command
	t_redir_list		*redir_list;
	int					pipe_left[2];
	int					pipe_right[2];
	t_list				**env;
	struct s_command	*next;
	struct s_command	*prev;
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
	t_list		*envp;
	char		*cmd_line;
	int			exit_code;
}	t_pipeline;

# include <builtins.h>

// parsing

int				parsing(char *str, t_list **inputs, t_list *env, t_pipeline **pipeline);
char			**newlines(char *str, size_t *input_nb);
void			break_into_words(t_list **inputs, char *inputs_array);
void			word_or_operator(t_list **inputs);
void			check_quote(t_esc *esc_status, char *str);
void			quotes_removal(void *content);
t_wd_desc		*new_wd_desc(int flags, char *word);
void	create_tree(t_list **inputs, \
	t_btree **holder, size_t size, t_list **env);
size_t	until_next_op(t_list **inputs);
void			addback_redir(t_redir_list **redir, t_redir_list *new);
t_bool			is_redir(t_list *inputs);
t_btree			*init_bst(t_list **env);
t_command		*init_cmd(t_list **env);
t_bool			check_validity_parenthesis(t_list *list);
void			new_branch(t_wd_desc *tok, t_btree \
				*holder, t_btree **tree);
void			is_between_p(t_list **inputs, t_btree **tree, t_list **env);
void			assignate_flags_dir(int tok_flags, \
				int *open_flags, int *fd);
void			check_quote_bis(t_esc *esc_status, char *str);
void			check_quote(t_esc *esc_status, char *str);
int			expansion(t_list **, t_list *env);
t_bool			check_expansion(t_exp **expansion, char *str);
char			*expand(char *str, t_list **env, int size);
char	*inspect_token(char *str, t_list **env);
char	*join_after_expansion(t_list **splitted_token);
void			create_argv(void *item);
void			fill_pipeline(t_pipeline **pipeline, t_btree *tree, t_list *env);
int			syntax_errors(t_list **inputs, t_list **env);
int			unclosed_quotes(char *str, t_list **env);
t_bool			is_char_exp(char c, int i);
char			**ft_esc_split(char *s, char *c);
void			second_tokenizing(t_list **inputs);
t_bool 			is_space_esc(t_esc stat, char c);
size_t			count_isspace(char *str);
int			red_experr_prompt(char *token, t_list **inputs, t_list **env);



/*
*	Error functions
*/
void	ft_error(void);
void	generic_error(t_pipeline *pipeline);
void	malloc_error(void);
void	fork_error(t_pipeline *pipeline);
void	dup2_error(void);
void	open_error(char *filename, t_pipeline *pipeline);
void	check_execve_error(char *pathname, t_pipeline *pipeline);
void	command_not_found_error(char *name, t_pipeline *pipeline);

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
//	Disable SIGINT and SIGQUIT during execution
void	set_exec_signals(void);

//	Signal handlers
void	rl_signals_handler(int sig);
void	exec_sig_handler(int sig);
void	heredoc_sig_handler(int sig);

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
*	Execution functions
*/
void	execute_pipeline(t_pipeline *pipeline);

// Utils
int		argv_size(char **av);
void	print_envp(t_list *envp);

	/*
	*	Manage t_pipeline structures
	*/

/*
*	Creates and initialize t_pipeline structure
*	Creates all pipes in its command list
*	No redirection is done at this time
*/
t_pipeline	*init_pipeline(t_command *cmd_lst, t_list *env);
void		destroy_pipeline(t_pipeline *pipeline);


/*
*	Redirections
*/
int			do_redirections(t_command *cmd, t_pipeline *pipeline);
void		set_pipes(t_pipeline *pipeline, t_command *cmd);

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
void	destroy_pid_list(t_pid_list **pid);

void	wait_all_pid(t_pid_list **pid_list, t_list **envp);

/*
*	Execution utils
*/
int		get_status(int status);
char	*get_bin_path(t_list *env, char *name);

//t_command utils

t_command	*command_last(t_command *command);
void		command_addback(t_command **list, t_command *new);
void		destroy_cmd_list(t_command **cmd);
void		destroy_cmd_one(t_command *cmd);

void	destroy_redir_list(t_redir_list **redir_list);

//NV A REMETTRE Dasn autre .h  apres mise en ordre du point h
//
void		set_hashtable(char **envp, t_list **env);
void		init_tracker(t_exp **exp_status);
int		ft_export(t_list **env, char **argv);
int			split_point(char *str);
int			*split_key_value(char **argv);
t_member	*env_fetch_member(t_member **member, size_t size);
void		export_expansion(char *str, t_hashtable *env);
int		exp_check_err(char *key);
int			ft_iscap(int a);
int			ft_unset(char **argv, t_list **env);
#endif
