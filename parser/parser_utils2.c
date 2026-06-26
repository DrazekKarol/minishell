/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 16:06:53 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/13 19:33:15 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*token_dup(t_token *token)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = token->type;
	if (token->value)
	{
		new_token->value = ft_strdup(token->value);
		if (!new_token->value)
			return (free(new_token), NULL);
	}
	return (new_token);
}

int	add_to_redirs(t_token **redirs, t_token **token_list)
{
	t_token	*temp;

	temp = token_dup((*token_list)->next);
	if (!temp)
		return (EXIT_FAILURE);
	temp->type = (*token_list)->type;
	add_token_back(redirs, temp);
	*token_list = (*token_list)->next;
	return (EXIT_SUCCESS);
}

t_exec_type	determine_exec_type(t_token *token)
{
	char	*cmd;

	if (!token)
		return (BINARY);
	cmd = token->value;
	if (ft_strncmp(cmd, BUILTIN_CD, ft_strlen(BUILTIN_CD) + 1) == 0
		|| ft_strncmp(cmd, BUILTIN_ECHO, ft_strlen(BUILTIN_ECHO) + 1) == 0
		|| ft_strncmp(cmd, BUILTIN_ENV, ft_strlen(BUILTIN_ENV) + 1) == 0
		|| ft_strncmp(cmd, BUILTIN_EXIT, ft_strlen(BUILTIN_EXIT) + 1) == 0
		|| ft_strncmp(cmd, BUILTIN_EXPORT, ft_strlen(BUILTIN_EXPORT) + 1) == 0
		|| ft_strncmp(cmd, BUILTIN_PWD, ft_strlen(BUILTIN_PWD) + 1) == 0
		|| ft_strncmp(cmd, BUILTIN_UNSET, ft_strlen(BUILTIN_UNSET) + 1) == 0)
		return (BUILTIN);
	return (BINARY);
}

t_op_type	get_op_type(t_token	**token_list)
{
	if (((*token_list)->type == TK_AND_OP || (*token_list)->type == TK_OR_OP
			|| (*token_list)->type == TK_PIPE)
		&& !is_token_parenthese((*token_list)->next)
		&& !is_token_redir((*token_list)->next)
		&& (*token_list)->next->type != TK_WORD)
	{
		syntax_error((*token_list)->next->type);
		return (UNKNOWN);
	}
	if ((*token_list)->type == TK_AND_OP)
		return (AND);
	else if ((*token_list)->type == TK_OR_OP)
		return (OR);
	else if ((*token_list)->type == TK_PIPE)
		return (PIPE);
	else
		return (UNKNOWN);
}

t_ast	*create_cmd_node(t_token **args, t_token **redirs)
{
	t_exec	*exec;

	exec = ft_calloc(1, sizeof(t_exec));
	if (!exec)
		return (free_tokens(*args), free_tokens(*redirs), NULL);
	exec->args = token_list_to_char_tab(*args);
	if (!exec->args)
		return (free_tokens(*redirs), NULL);
	exec->redirs = *redirs;
	exec->type = determine_exec_type(*args);
	free_tokens(*args);
	*args = NULL;
	*redirs = NULL;
	return (new_cmd_node(exec));
}
