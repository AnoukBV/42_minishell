/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 08:56:43 by aboulore          #+#    #+#             */
/*   Updated: 2024/06/05 11:07:36 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

// parsing
char		**newlines(char *str, size_t *input_nb);
int			parsing(char *str, t_list **inputs, \
				t_list *env, t_pipeline **pipeline);

// errors
int			unclosed_quotes(char *str, t_list **env);
int			red_experr_prompt(char *token, t_list **inputs, t_list **env);
int			syntax_errors(t_list **inputs, t_list **env);

// quotes
void		check_quote(t_esc *esc_status, char *str);
void		check_quote_bis(t_esc *esc_status, char *str);
void		quotes_removal(void *content);
t_wd_desc	*new_wd_desc(int flags, char *word);

// tokenizing
void		break_into_words(t_list **inputs, char *inputs_array);
void		word_or_operator(t_list **inputs);
char		**ft_esc_split(char *s, char *c);
void		second_tokenizing(t_list **inputs);
t_bool		is_space_esc(t_esc stat, char c);
size_t		count_isspace(char *str);
char		**free_split(char **split, int len_split);

// expansion
int			expansion(t_list **inputs, t_list *env);
t_bool		check_expansion(t_exp **expansion, char *str);
char		*expand(char *str, t_list **env, int size);
char		*inspect_token(char *str, t_list **env);
char		*join_after_expansion(t_list **splitted_token);
t_bool		is_char_exp(char c, int i);
void		init_tracker(t_exp **exp_status);

// from tokens to commands
void		create_tree(t_list **inputs, \
				t_btree **holder, size_t size, t_list **env);
size_t		until_next_op(t_list **inputs);
void		addback_redir(t_redir_list **redir, t_redir_list *new);
t_btree		*init_bst(t_list **env);
t_command	*init_cmd(t_list **env);
void		new_branch(t_wd_desc *tok, t_btree \
				*holder, t_btree **tree);
t_command	*command_last(t_command *command);
void		command_addback(t_command **list, t_command *new);

// heredoc and redirections
void		assignate_flags_dir(int tok_flags, \
			int *open_flags, int *fd);
t_bool		is_redir(t_list *inputs);

// creating the pipeline
t_pipeline	*init_pipeline(t_command *cmd_lst, t_list *env);
void		prepare_pipeline(t_pipeline *pipeline);
void		create_argv(void *item);
void		fill_pipeline(t_pipeline **pipeline, t_btree *tree, t_list *env);

// memory
void		free_before_id(t_list *inputs, size_t in_nb);
void		del_wddesc(void *word);

#endif
