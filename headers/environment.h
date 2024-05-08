/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:45:42 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/09 00:44:09 by aboulore         ###   ########.fr       */
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



#endif
