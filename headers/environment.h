/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:45:42 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/23 14:22:23 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

typedef struct	s_member
{
	char	*key;
	char	*value;
	t_bool	is_og;
}	t_member;

typedef struct	s_hashtable
{
	struct s_member	**member;
	size_t			size;
}	t_hashtable;

t_member	*get_env_element(t_list *env, char *key);
char		**get_path_list(t_list	*env);

void	del_member(void *content);
int	print_env(t_list **env, int key);
char	*env_find_key(char *key, t_list	**env);
t_member	*env_find_tmemb(char *key, t_list **env);
t_member	*create_table_member(char *key, char *value, t_bool is_og);
int		ft_exp_p(t_list **e);
char		**transform_envp(t_list *env);

// free memory
void	free_env_member(void *elem);	
int	ft_exp_err_mess(char *wrong);
void	free_env_list(t_list **env_list);
int	ft_exp_option_mess(char str);

#endif
