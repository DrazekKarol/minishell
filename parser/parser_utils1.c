/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 16:02:30 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/12 16:04:10 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

float	get_lbp(t_op_type op_type)
{
	if (op_type == AND || op_type == OR)
		return (AND_OR_OP_LBP);
	if (op_type == PIPE)
		return (PIPE_OP_LBP);
	return (-1.0);
}

float	get_rbp(t_op_type op_type)
{
	if (op_type == AND || op_type == OR)
		return (AND_OR_OP_RBP);
	if (op_type == PIPE)
		return (PIPE_OP_RBP);
	return (-1.0);
}

bool	is_token_operator(t_token *token)
{
	if (!token)
		return (false);
	if (token->type == TK_AND_OP || token->type == TK_OR_OP
		|| token->type == TK_PIPE)
		return (true);
	return (false);
}

bool	is_token_redir(t_token *token)
{
	if (!token)
		return (false);
	if (token->type == TK_REDIR_IN || token->type == TK_REDIR_OUT
		|| token->type == TK_REDIR_HEREDOC || token->type == TK_REDIR_APPEND)
		return (true);
	return (false);
}

bool	is_token_parenthese(t_token *token)
{
	if (!token)
		return (false);
	if (token->type == TK_LPARENTHESE || token->type == TK_RPARENTHESE)
		return (true);
	return (false);
}
