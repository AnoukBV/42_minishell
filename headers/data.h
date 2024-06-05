/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:46:30 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/05 09:52:12 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "minishell.h"

typedef enum e_bool { false, true }	t_bool;

typedef struct s_member
{
	char	*key;
	char	*value;
	t_bool	is_og;
}	t_member;

typedef struct s_hashtable
{
	struct s_member	**member;
	size_t			size;
}	t_hashtable;

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

/*
*	A list of file descriptors to close before calling execve()
*/
typedef struct s_fd_list
{
	int					fd;
	struct s_fd_list	*next;
}	t_fd_list;

/*
*	A list of child processes pid
*/
typedef struct s_pid_list
{
	int					pid;
	struct s_pid_list	*next;
}	t_pid_list;

typedef struct s_redir_list
{
	int						fd_to_redirect;
	char					*target_filename;
	int						open_flags;
	struct s_redir_list		*next;
}	t_redir_list;

typedef struct s_command
{
	int					flags;
	t_bool				is_argv;
	void				*argv;
	char				*command;
	t_redir_list		*redir_list;
	int					pipe_left[2];
	int					pipe_right[2];
	t_list				**env;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_pipeline
{
	t_command	*cmd_list;
	t_fd_list	*fd_list;
	t_pid_list	*pid_list;
	t_list		*envp;
	char		*cmd_line;
	int			exit_code;
}	t_pipeline;

#endif