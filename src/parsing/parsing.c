/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:33:37 by aboulore          #+#    #+#             */
/*   Updated: 2024/04/24 13:10:34 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	parsing(char *str, t_list **inputs)
{
	size_t		input_nb;
	char		**inputs_arr;

//lexer
	inputs_arr = newlines(str, &input_nb);
	print_2d_array(inputs_arr);
	if (input_nb > 1)
	{
		return (-1);
	}
	ft_putstr("\n\n"); //DELETE
	break_into_words(inputs, inputs_arr); 
	word_or_operator(inputs);
	print_unidentified_tokens(input_nb, *inputs); //DELETE

//	identification;

//	parser

	return (input_nb);
}
