/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:45:42 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/05 09:52:25 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# define ENV_KEY_EXIT_CODE "EXITCODE"

// parsing the environment
void		set_hashtable(char **envp, t_list **env);
t_member	*create_table_member(char *key, char *value, t_bool is_og);
char		**transform_envp(t_list *env);

// browsing the environment
t_member	*get_env_element(t_list *env, char *key);
char		**get_path_list(t_list	*env);
char		*env_find_key(char *key, t_list	**env);
t_member	*env_find_tmemb(char *key, t_list **env);

// export and unset
int			ft_export(t_list **env, char **argv);
int			split_point(char *str);
int			*split_key_value(char **argv);
int			exp_check_err(char *key);
int			ft_iscap(int a);
int			ft_unset(char **argv, t_list **env);
void		del_member(void *content);

// display
int			ft_exp_p(t_list **e);
int			print_env(t_list **env, int key);
int			argv_size(char **av);
void		print_envp(t_list *envp);

// update env variables without calling ft_export
void		update_env_element(t_list **env_lst, char *key, char *value);
void		update_env_exit_code(t_list **env_lst, int exit_code);

// free memory
void		free_env_member(void *elem);	
int			ft_exp_err_mess(char *wrong, char *search);
void		free_env_list(t_list **env_list);
int			ft_exp_option_mess(char str);

#endif
