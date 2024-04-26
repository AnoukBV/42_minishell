/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:45:42 by aboulore          #+#    #+#             */
/*   Updated: 2024/04/26 12:45:13 by aboulore         ###   ########.fr       */
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

void	set_hashtable(char **envp, t_hashtable **env);
void	delmemb_env(t_member *member);
void	free_env(t_hashtable *env);

#endif
