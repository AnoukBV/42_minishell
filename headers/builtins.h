/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:46:08 by abernade          #+#    #+#             */
/*   Updated: 2024/06/05 09:52:40 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		builtin_cd(char **av, t_list **env);
int		builtin_pwd(void);
int		builtin_echo(char **argv);
int		builtin_export(char **argv, t_list **envp);
void	builtin_exit(t_pipeline *pipeline, t_command *cmd);
t_bool	is_builtin(char *cmd_name);

#endif