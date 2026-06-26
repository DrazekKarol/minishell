/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:23:22 by mstepnic          #+#    #+#             */
/*   Updated: 2026/01/16 17:25:15 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*nud(t_token **token_list)
{
	t_ast	*node;
	t_ast	*subsh;

	if ((*token_list)->type == TK_WORD || is_token_redir(*token_list))
		node = get_cmd_node(token_list);
	else if ((*token_list)->type == TK_LPARENTHESE)
	{
		*token_list = (*token_list)->next;
		subsh = create_ast(token_list, 0.0);
		if (!subsh)
			return (NULL);
		*token_list = (*token_list)->next;
		node = new_subsh_node(subsh);
	}
	else
		return (NULL);
	return (node);
}

t_ast	*get_ast(t_token	**token_list, t_ast *left, float min_bp)
{
	t_ast		*curr;
	float		lbp;
	float		rbp;
	t_op_type	op_type;

	while (*token_list && (*token_list)->type != TK_EOF)
	{
		if ((*token_list)->type == TK_RPARENTHESE)
			break ;
		op_type = get_op_type(token_list);
		if (op_type == UNKNOWN)
			return (free_ast(left), NULL);
		lbp = get_lbp(op_type);
		if (lbp < min_bp)
			break ;
		rbp = get_rbp(op_type);
		*token_list = (*token_list)->next;
		curr = new_op_node(op_type, left, create_ast(token_list, rbp));
		if (!curr || !curr->data.op.right)
			return (free_ast(left), NULL);
		left = curr;
	}
	return (left);
}

t_ast	*create_ast(t_token **token_list, float min_bp)
{
	t_ast		*left;

	left = nud(token_list);
	if (!left)
		return (NULL);
	left = get_ast(token_list, left, min_bp);
	return (left);
}

t_ast	*parser(t_data *data)
{
	t_ast	*ast;
	t_token	*token_list;

	token_list = data->token_list;
	if (validate(token_list) == EXIT_FAILURE)
	{
		data->exit_status = 2;
		return (NULL);
	}
	ast = NULL;
	if (handle_envs(data, token_list) == EXIT_FAILURE
		|| handle_wildcards(token_list) == EXIT_FAILURE
		|| handle_quotes(token_list) == EXIT_FAILURE)
		return (NULL);
	token_list = remove_empty_tokens(token_list);
	data->token_list = token_list;
	ast = create_ast(&token_list, 0.0);
	return (ast);
}
