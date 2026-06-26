/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:35:33 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/12 16:43:53 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "libft.h"

t_ast	*new_cmd_node(t_exec *exec_list)
{
	t_ast	*new_node;

	new_node = ft_calloc(1, sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->type = COMMAND;
	new_node->data.exec = exec_list;
	return (new_node);
}

t_ast	*new_op_node(t_op_type op_type, t_ast *left, t_ast *right)
{
	t_ast	*new_node;

	new_node = ft_calloc(1, sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->type = OPERATOR;
	new_node->data.op.type = op_type;
	new_node->data.op.left = left;
	new_node->data.op.right = right;
	return (new_node);
}

t_ast	*new_subsh_node(t_ast *subsh)
{
	t_ast	*new_node;

	new_node = ft_calloc(1, sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->type = SUBSHELL;
	new_node->data.subsh = subsh;
	return (new_node);
}

void	free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->type == COMMAND)
	{
		free_exec(ast->data.exec);
		free(ast);
	}
	else if (ast->type == OPERATOR)
	{
		if (ast->data.op.left)
			free_ast(ast->data.op.left);
		if (ast->data.op.right)
			free_ast(ast->data.op.right);
		free(ast);
	}
	else if (ast->type == SUBSHELL)
	{
		if (ast->data.subsh)
			free_ast(ast->data.subsh);
		free(ast);
	}
}
