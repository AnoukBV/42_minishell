/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspect_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:05:16 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/04 12:38:51 by aboulore         ###   ########.fr       */
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
	//printf("\n[isolate_not_exp] begin = %i and i = %i\n", save, i);
	add = ft_substr(str, save, i - save);
	//printf("\n[isolate_not_exp] char* to be added to **split: %s\n", add);
	new = ft_lstnew(add);
	ft_lstadd_back(split, new);
}

static int	isolate_exp(char *str, t_list **env, t_list **split, t_esc *stat)
{
	t_list	*new;
	char	*add;
	//char	*res;
	int	i;

	i = 1;
	new = NULL;
	if (!str[i] || (ft_isspace(str[i]) || (is_char_exp(str[i], 1) == false && (str[i] != '?' && \
		((str[i] != '"' && str[i] != '\'') || (stat->is_quoted == true && str[i] == '"'))))))
	{
		ft_lstadd_back(split, ft_lstnew(ft_strdup("$")));
		return (i);
	}
	while (str[i] && (is_char_exp(str[i], i) == true || str[i] == '?'))
	{
		check_quote(stat, &str[i]);
		i++;
	}
	//printf("\n%c\n", str[1]);
	//if (str[1] == '?')
	//{
	//	add = expand("?", env, 2);
	//	printf("\n%s\n", add);
	//	add = ft_strjoin(res, expand(&str[1], env, i - 1));
	//	i = 2;
	//}
	//else
		add = expand(str, env, i);
		//printf("\nIn isolate_exp, char* to be added to **split: %s\n", add);
	if (add)
	{
		new = ft_lstnew(add);
		ft_lstadd_back(split, new);
	}
	if (str[1] == '?')
		i = 2;
	//printf("\n[isolate_exp] size of new inputs list: %d\n", ft_lstsize(new));
	return (i);
}

char	*inspect_token(char *str, t_list **env, int flag, t_list **inputs)
{
	int	i;
	int	begin;
	//int end;
	t_list	*split;
	t_esc	stat;

	i = 0;
	split = NULL;
	stat.is_quoted = false;
	begin = i;
	while ((size_t)i < ft_strlen(str) || str[i])
	{
		check_quote(&stat, &str[i]);
		//printf("\nstr[0][i]=%c\n", str[0][i]);
		if ((str[i] == '$' && stat.is_quoted == false) || (str[i] == '$' && \
			stat.is_quoted == true && stat.is_simplequote == false))
		{
		//	printf("\n[inspect_token] &str[0][i] before isolate_not_exp: %s\n", &str[0][begin]);
			isolate_not_exp(begin, i, str, &split);
		//	printf("\n[inspect_token] &str[0][i] before isolate_exp: %s\n", &str[0][i]);
			i += isolate_exp(&str[i], env, &split, &stat);
			begin = i;
	//		end = i;
		//	printf("\n[inspect_token] str[end(=%i)] after isolate_exp: %c\n", end, str[0][end]);
		//	printf("\n[inspect_token] &str[0][i (=%i)] after isolate_exp: %s\n", i, &str[0][i]);
		}
		else
			i++;
		
	}
	//printf("\n[inspect_token] str[end(=%i)] after while loop: %c\n", end, str[0][end]);
	if (begin != (int)ft_strlen(str))
		isolate_not_exp(begin, i, str, &split);
	if (split)
		return (join_after_expansion(&split, flag, str, inputs));
	return (NULL);

}
