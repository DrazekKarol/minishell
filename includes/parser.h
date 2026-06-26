/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:23:34 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/13 21:02:23 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <dirent.h>
# include <stdbool.h>
# include "defines.h"
# include "libft.h"

// parser/parser.c
t_ast		*create_ast(t_token **token_list, float min_bp);

// parser/extend_envs.c
int			handle_envs(t_data *data, t_token *tokens);

// parser/extend_wildcards.c
int			handle_wildcards(t_token *tokens);

// parser/process_quotes.c
int			handle_quotes(t_token *tokens);

// parser/validate.c
int			validate(t_token *token_list);
void		syntax_error(t_token_type tk_type);

// parser/extend_utils.c
int			get_env_name_len(char *token_value, int is_in_quotes);
size_t		count_words(char const *s);
int			matches_pattern(char *filename, char **patterns);
int			add_tokens_to_list(t_token *token, t_list *matched_files);

// parser/parser_utils1.c
float		get_lbp(t_op_type op_type);
float		get_rbp(t_op_type op_type);
bool		is_token_operator(t_token *token);
bool		is_token_redir(t_token *token);
bool		is_token_parenthese(t_token *token);

// parser/parser_utils2.c
t_token		*token_dup(t_token *token);
int			add_to_redirs(t_token **redirs_in, t_token **token_list);
t_exec_type	determine_exec_type(t_token *token);;
t_op_type	get_op_type(t_token	**token_list);;
t_ast		*create_cmd_node(t_token **args, t_token **redirs);

// parser/parser_utils3.c
t_token		*remove_empty_tokens(t_token *token_list);
int			handle_redirs(t_token **token_list, t_token **args,
				t_token **redirs_in);
t_ast		*get_cmd_node(t_token **token_list);

#endif