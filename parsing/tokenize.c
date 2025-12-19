/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:25:02 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/03 16:34:18 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token_type	get_redir_type(char *cmd, int *i)
{
	if (cmd[*i] == '<' && cmd[*i + 1] == '<')
	{
		(*i) += 2;
		return (HEREDOC);
	}
	else if (cmd[*i] == '>' && cmd[*i + 1] == '>')
	{
		(*i) += 2;
		return (REDIR_APPEND);
	}
	else if (cmd[*i] == '<')
	{
		(*i)++;
		return (REDIR_IN);
	}
	else if (cmd[*i] == '>')
	{
		(*i)++;
		return (REDIR_OUT);
	}
	return (ARG);
}

t_token	*handle_redir(char *cmd, int *i)
{
	t_token	*new_token;
	int		start;
	int		redir_type;
	int		is_in_quotes;

	redir_type = get_redir_type(cmd, i);
	while (cmd[*i] && (cmd[*i] == '<' || cmd[*i] == '>' || ft_isspace(cmd[*i])))
		(*i)++;
	start = *i;
	is_in_quotes = 0;
	while (cmd[*i] && (!ft_isspace(cmd[*i]) || is_in_quotes))
	{
		if ((cmd[*i] == '\'' || cmd[*i] == '\"') && !is_in_quotes)
			is_in_quotes = cmd[*i];
		else if (cmd[*i] == is_in_quotes)
			is_in_quotes = 0;
		if (!is_in_quotes && (cmd[*i] == '<' || cmd[*i] == '>'))
			break ;
		(*i)++;
	}
	new_token = create_token(ft_substr(cmd, start, *i - start), redir_type);
	return (new_token);
}

t_token	*get_token(char *cmd, int *i)
{
	t_token	*new_token;
	int		start;
	int		is_in_quotes;

	start = *i;
	is_in_quotes = 0;
	if (cmd[*i] == '<' || cmd[*i] == '>')
		new_token = handle_redir(cmd, i);
	else
	{
		while (cmd[*i] && (!ft_isspace(cmd[*i]) || is_in_quotes))
		{
			if ((cmd[*i] == '\'' || cmd[*i] == '\"') && !is_in_quotes)
				is_in_quotes = cmd[*i];
			else if (cmd[*i] == is_in_quotes)
				is_in_quotes = 0;
			if (!is_in_quotes && (cmd[*i] == '<' || cmd[*i] == '>'))
				break ;
			(*i)++;
		}
		new_token = create_token(ft_substr(cmd, start, *i - start), ARG);
	}
	return (new_token);
}

void	type_controll(t_token *tokens)
{
	while (tokens && tokens->type != ARG)
		tokens = tokens->next;
	if (tokens)
		tokens->type = EXEC;
}

t_token	*tokenize_input(char *cmd)
{
	t_token	*tokens;
	t_token	*new_token;
	int		i;

	i = 0;
	tokens = NULL;
	while (cmd[i])
	{
		while (cmd[i] && ft_isspace(cmd[i]))
			i++;
		if (!cmd[i])
			break ;
		new_token = get_token(cmd, &i);
		if (!new_token)
		{
			free_tokens(tokens);
			return (NULL);
		}
		add_token(&tokens, new_token);
	}
	type_controll(tokens);
	return (tokens);
}
