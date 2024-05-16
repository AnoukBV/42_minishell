/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:45:42 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/16 11:05:09 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H


typedef struct	s_member
{
	char	*key;
	char	*value;
}	t_member;

typedef struct	s_hashtable
{
	struct s_member	**member;
	size_t			size;
}	t_hashtable;

t_member	*get_env_element(t_hashtable *env, char *key);
char		**get_path_list(t_hashtable	*env);

#endif
