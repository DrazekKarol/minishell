/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 17:47:41 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/13 21:17:41 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <error.h>

void	syntax_error(t_token_type tk_type)
{
	ft_putstr_fd("minishit: syntax error near unexpected token ", 2);
	if (tk_type == TK_EOF)
		ft_putstr_fd("`newline'\n", STDERR_FILENO);
	if (tk_type == TK_PIPE)
		ft_putstr_fd("`|'\n", STDERR_FILENO);
	if (tk_type == TK_AND_OP)
		ft_putstr_fd("`&&'\n", STDERR_FILENO);
	if (tk_type == TK_OR_OP)
		ft_putstr_fd("`||'\n", STDERR_FILENO);
	if (tk_type == TK_LPARENTHESE)
		ft_putstr_fd("`('\n", STDERR_FILENO);
	if (tk_type == TK_RPARENTHESE)
		ft_putstr_fd("`)'\n", STDERR_FILENO);
	if (tk_type == TK_REDIR_IN)
		ft_putstr_fd("`<'\n", STDERR_FILENO);
	if (tk_type == TK_REDIR_OUT)
		ft_putstr_fd("`>'\n", STDERR_FILENO);
	if (tk_type == TK_REDIR_HEREDOC)
		ft_putstr_fd("`<<'\n", STDERR_FILENO);
	if (tk_type == TK_REDIR_APPEND)
		ft_putstr_fd("`>>'\n", STDERR_FILENO);
}

int	validate_quotes(char *input)
{
	int	i;
	int	squotes;
	int	dquotes;

	i = 0;
	squotes = 0;
	dquotes = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !dquotes)
			squotes = !squotes;
		else if (input[i] == '\"' && !squotes)
			dquotes = !dquotes;
		i++;
	}
	if (squotes || dquotes)
	{
		printf("unclosed quotes\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	validate_parentheses(t_token *token_list)
{
	t_token	*temp;
	int		lparens;
	int		rparens;

	temp = token_list;
	lparens = 0;
	rparens = 0;
	while (temp)
	{
		if (temp->type == TK_LPARENTHESE)
			lparens++;
		else if (temp->type == TK_RPARENTHESE)
			rparens++;
		temp = temp->next;
	}
	if (lparens > rparens)
		return (printf("unclosed parentheses\n"), EXIT_FAILURE);
	else if (lparens < rparens)
		return (printf("syntax error near unexpected token ')'\n"),
			EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	validate_first_token(t_token *token)
{
	if (token->type == TK_PIPE || token->type == TK_AND_OP
		|| token->type == TK_OR_OP || token->type == TK_RPARENTHESE)
	{
		syntax_error(token->type);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	validate(t_token *token_list)
{
	if (validate_first_token(token_list)
		|| validate_parentheses(token_list) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (token_list)
	{
		if (token_list->value && (ft_strchr(token_list->value, '\'')
				|| ft_strchr(token_list->value, '\"'))
			&& validate_quotes(token_list->value))
			return (EXIT_FAILURE);
		token_list = token_list->next;
	}
	return (EXIT_SUCCESS);
}
