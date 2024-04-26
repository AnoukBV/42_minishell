/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:50:36 by aboulore          #+#    #+#             */
/*   Updated: 2024/04/26 13:54:31 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# define MALLOC_ERR	9

# define EXPORT 1
# define ENV	0

typedef enum	e_type
{
	T_WORD = 0,
	T_OPEN,
	T_CLOSE,
	T_PIPE,
	T_OR,
	T_AND,
	T_RED_OUT,
	T_APP_OUT,
	T_RED_IN,
	T_APP_IN
}	t_type;

#endif
