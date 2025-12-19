/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrazek <kdrazek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:19:22 by mstepnic          #+#    #+#             */
/*   Updated: 2025/12/19 14:39:28 by kdrazek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <dirent.h>
# include "defines.h"
# include "envs.h"

int			validate_input(t_data *data, char *input);
int			check_for_unexpected_token(char *input);

t_list		*split_commands(char *input);
t_token		*tokenize_input(char *cmd);
int			parse_tokens(t_data *data, t_exec *exec, t_token *tokens,
				int command_index);
int			handle_envs(t_data *data, t_token *tokens);
void		process_quotes(t_token *tokens);
int			handle_wildcards(t_token *tokens);

int			extend_env(t_data *data, char **token_value, int is_in_quotes,
				int *i);
int			get_env_name_len(char *token_value, int is_in_quotes);
size_t		count_words(char const *s);
int			matches_pattern(char *filename, char **patterns);
int			add_tokens_to_list(t_token *token, t_list *matched_files);

t_exec_type	determine_exec_type(char *cmd);
int			determine_append_mode(t_token *tokens);
t_exec		*create_exec_list(int nb_of_commands);
void		free_exec_list(t_exec *head);

t_token		*create_token(char *value, t_token_type type);
void		add_token(t_token **head, t_token *new_token);
void		add_token_after(t_token *node, t_token *new_token);
void		free_tokens(t_token *head);
size_t		count_tokens(t_token *tokens, t_token_type type);

#endif