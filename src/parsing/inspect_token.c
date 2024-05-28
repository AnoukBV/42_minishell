/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspect_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:05:16 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/28 18:37:53 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static void	isolate_not_exp(int save, int i, char *str, t_list **split)
{
	t_list	*new;
	char	*add;

	new = NULL;
	if (i - save < 1)
		return ;
	printf("\n[isolate_not_exp] begin = %i and i = %i\n", save, i);
	add = ft_substr(str, save, i - save);
	printf("\n[isolate_not_exp] char* to be added to **split: %s\n", add);
	new = ft_lstnew(add);
	ft_lstadd_back(split, new);
}

static int	isolate_exp(char *str, t_list **env, t_list **split, t_esc *stat)
{
	t_list	*new;
	char	*add;
	int	i;

	i = 1;
	while (str[i] && is_char_exp(str[i], i) == true)
	{
		check_quote(stat, &str[i]);
		i++;
	}
	if (i == 1)
		ft_lstadd_back(split, ft_lstnew("$"));
	else if (i > 1)
	{
		add = expand(str, env, i);
		printf("\nIn isolate_exp, char* to be added to **split: %s\n", add);
		new = ft_lstnew(add);
		ft_lstadd_back(split, new);
	}
	return (i);
}

void	inspect_token(char **str, t_list **env)
{
	int	i;
	int	begin;
	int end;
	t_list	*split;
	t_esc	stat;

	i = 0;
	split = NULL;
	stat.is_quoted = false;
	begin = i;
	while ((size_t)i < ft_strlen(str[0]) || str[0][i])
	{
		check_quote(&stat, &str[0][i]);
		printf("\nstr[0][i]=%c\n", str[0][i]);
		if ((str[0][i] == '$' && stat.is_quoted == false) || (str[0][i] == '$' && \
			stat.is_quoted == true && stat.is_simplequote == false))
		{
			printf("\n[inspect_token] &str[0][i] before isolate_not_exp: %s\n", &str[0][begin]);
			isolate_not_exp(begin, i, str[0], &split);
			printf("\n[inspect_token] &str[0][i] before isolate_exp: %s\n", &str[0][i]);
			i += isolate_exp(&str[0][i], env, &split, &stat);
			begin = i;
			end = i;
			printf("\n[inspect_token] str[end(=%i)] after isolate_exp: %c\n", end, str[0][end]);
			printf("\n[inspect_token] &str[0][i (=%i)] after isolate_exp: %s\n", i, &str[0][i]);
		}
		else
			i++;
		
	}
	printf("\n[inspect_token] str[end(=%i)] after while loop: %c\n", end, str[0][end]);
	if (end != (int)ft_strlen(str[0]))
		isolate_not_exp(end, i, str[0], &split);
	if (split)
		join_after_expansion(&str[0], &split);
	ft_lstclear(&split, free);

}
