/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:25:50 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/26 13:49:49 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

// Execution functions
void	execute_pipeline(t_pipeline *pipeline);
int		do_redirections(t_command *cmd, t_pipeline *pipeline);
void	set_pipes(t_pipeline *pipeline, t_command *cmd);

// Manage t_fd_list structures
int		remove_fd(int fd, t_fd_list **fds);
void	close_fd_list(t_fd_list **fds);
void	add_fd(int fd, t_fd_list **fds);

// Manage t_pid_list structures
void	add_pid(int pid, t_pid_list **pid_list);
void	remove_pid(int pid, t_pid_list **pid_list);
void	destroy_pid_list(t_pid_list **pid);
void	wait_all_pid(t_pid_list **pid_list, t_list **envp);

// Execution utils
int		get_status(int status);
char	*get_bin_path(t_list *env, char *name, t_pipeline *pipeline);
t_bool	is_directory(const char *pathname);

// Memory
void	destroy_cmd_list(t_command **cmd, t_bool rm_heredoc);
void	destroy_cmd_one(t_command *cmd, t_bool rm_heredoc);
void	destroy_redir_list(t_redir_list **redir_list, t_bool rm_heredoc);
void	destroy_pipeline(t_pipeline *pipeline, int x, t_bool rm_heredoc);

// builtin execution
void	builtin_exec(t_command *cmd, t_pipeline *pipeline, t_bool will_exit);
void	simple_builtin_exec(t_command *cmd, t_pipeline *pipeline);

#endif