/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:46:45 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/13 19:12:01 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	is_next_token(char *input, int quote, int *i)
{
	if (ft_isspace(input[*i]) && !quote)
	{
		return (true);
	}
	if (!quote && (input[*i] == '|'
			|| input[*i] == '<' || input[*i] == '>'
			|| input[*i] == '(' || input[*i] == ')'
			|| (input[*i] == '&' && input[*i + 1] == '&')))
		return (true);
	return (false);
}

t_token	*get_word(char *input, int *i)
{
	t_token	*new_token;
	int		start;
	int		quote;

	start = *i;
	quote = 0;
	while (input[*i] && (!ft_isspace(input[*i]) || quote))
	{
		if (input[*i] == '\'' || input[*i] == '\"')
		{
			quote = input[(*i)++];
			while (input[*i] != quote)
				(*i)++;
			quote = 0;
		}
		if (is_next_token(input, quote, i))
			break ;
		if (input[*i])
			(*i)++;
	}
	new_token = token_new(TK_WORD, ft_substr(input, start, *i - start));
	if (!new_token->value)
		return (free(new_token), NULL);
	return (new_token);
}

t_token	*get_token(char	*input, int *i)
{
	if (input[*i] == '<' && input[*i + 1] == '<')
		return (*i += 2, token_new(TK_REDIR_HEREDOC, NULL));
	if (input[*i] == '>' && input[*i + 1] == '>')
		return (*i += 2, token_new(TK_REDIR_APPEND, NULL));
	if (input[*i] == '<')
		return ((*i)++, token_new(TK_REDIR_IN, NULL));
	if (input[*i] == '>')
		return ((*i)++, token_new(TK_REDIR_OUT, NULL));
	if (input[*i] == '&' && input[*i + 1] == '&')
		return (*i += 2, token_new(TK_AND_OP, NULL));
	if (input[*i] == '|' && input[*i + 1] == '|')
		return (*i += 2, token_new(TK_OR_OP, NULL));
	if (input[*i] == '|')
		return ((*i)++, token_new(TK_PIPE, NULL));
	if (input[*i] == '(')
		return ((*i)++, token_new(TK_LPARENTHESE, NULL));
	if (input[*i] == ')')
		return ((*i)++, token_new(TK_RPARENTHESE, NULL));
	return (get_word(input, i));
}

t_token	*lexer(t_data *data)
{
	t_token	*token_list;
	t_token	*new_token;
	int		i;

	i = 0;
	token_list = NULL;
	while (data->input[i])
	{
		while (data->input[i] && ft_isspace(data->input[i]))
			i++;
		new_token = get_token(data->input, &i);
		if (!new_token)
			return (free_tokens(token_list), NULL);
		add_token_back(&token_list, new_token);
	}
	new_token = token_new(TK_EOF, NULL);
	if (!new_token)
		return (free_tokens(token_list), NULL);
	add_token_back(&token_list, new_token);
	data->token_list = token_list;
	return (token_list);
}
