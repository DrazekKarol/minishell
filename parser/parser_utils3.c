/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 16:26:43 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/13 21:30:13 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_all_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (false);
		i++;
	}
	return (true);
}

t_token	*remove_empty_tokens(t_token *token_list)
{
	t_token	*temp;
	t_token	*new_token_list;
	t_token	*new_node;

	new_token_list = NULL;
	temp = token_list;
	while (temp)
	{
		if (temp->type == TK_WORD
			&& (!temp || is_all_spaces(temp->value)))
		{
			temp = temp->next;
			continue ;
		}
		new_node = token_dup(temp);
		if (!new_node)
			return (free_tokens(new_token_list), free_tokens(token_list),
				NULL);
		add_token_back(&new_token_list, new_node);
		temp = temp->next;
	}
	free_tokens(token_list);
	return (new_token_list);
}

int	handle_redirs(t_token **token_list, t_token **args, t_token **redirs)
{
	if ((*token_list)->next->type != TK_WORD)
	{
		syntax_error((*token_list)->next->type);
		return (EXIT_FAILURE);
	}
	if (add_to_redirs(redirs, token_list))
	{
		free_tokens(*args);
		free_tokens(*redirs);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

t_ast	*get_cmd_node(t_token **token_list)
{
	t_token	*args;
	t_token	*redirs;

	args = NULL;
	redirs = NULL;
	while ((*token_list)->type != TK_EOF && (*token_list)->type != TK_PIPE
		&& (*token_list)->type != TK_AND_OP && (*token_list)->type != TK_OR_OP)
	{
		if ((*token_list)->type == TK_WORD)
			add_token_back(&args, token_dup(*token_list));
		else if (is_token_redir(*token_list)
			&& handle_redirs(token_list, &args, &redirs))
			return (NULL);
		else if (is_token_parenthese(*token_list)
			&& !is_token_parenthese((*token_list)->next)
			&& !is_token_operator((*token_list)->next)
			&& (*token_list)->next->type != TK_EOF)
			return (syntax_error((*token_list)->type), NULL);
		else if ((*token_list)->type == TK_RPARENTHESE)
			break ;
		*token_list = (*token_list)->next;
	}
	return (create_cmd_node(&args, &redirs));
}
