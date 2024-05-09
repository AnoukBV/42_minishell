/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspect_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:05:16 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/09 17:04:40 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	isolate_not_exp(char *str, t_bool exp, t_exp **exp_status, \
		t_list **splitted_token)
{
	size_t	i;
	t_list	*new;

	i = 0;
	while (str[i] && exp == false && str[i] != '$')
	{
		i++;
		exp = check_expansion(exp_status, &str[i]);
	}
	if (i != 0)
	{
		new = ft_lstnew(ft_substr(str, 0, i));
		ft_lstadd_back(splitted_token, new);
	}
	if (str[i] == '\"' && exp == true)
	{
		i -= 1;
		(*exp_status)->is_exp_quo = false;
		(*exp_status)->esc_status->is_quoted = false;
	}
	return (i);
}

static size_t	isolate_exp(char *str, t_hashtable **env, \
		t_exp **exp_status, t_list **splitted_token)
{
	t_list	*new;
	t_bool	exp;
	size_t	i;

	i = 0;
	exp = true;
	while (str[i] && exp == true)
	{
		i++;
		exp = check_expansion(exp_status, &str[i]);
	}
	if (i != 0)
	{
		new = ft_lstnew(expand(str, env, i + 2));
		ft_lstadd_back(splitted_token, new);
	}
	return (i);
}

void	inspect_token(char **str, t_hashtable **env)
{
	size_t	i;
	t_list	*splitted_token;
	t_bool	exp;
	t_exp	*exp_status;

	i = 0;
	splitted_token = NULL;
	init_tracker(&exp_status);
//	if (!str && !(*str) && !(**str))
//		return ;
	while (str[0][i] != 0)
	{
		exp = check_expansion(&exp_status, &str[0][i]);
		if (exp == false)
			i += isolate_not_exp(&str[0][i], exp, &exp_status, &splitted_token);
		else if (str[0][i])
			i += isolate_exp(&str[0][i], env, &exp_status, &splitted_token);
		i++;
	}
	if (splitted_token)
		join_after_expansion(&str[0], &splitted_token);
	//printf("%s\n", *str);
	free(exp_status->esc_status);	
	free(exp_status);	
	ft_lstclear(&splitted_token, free);
}
