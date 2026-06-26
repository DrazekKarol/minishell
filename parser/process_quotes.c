/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:48:33 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/12 15:57:22 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	remove_quotes(char *input, int quote)
{
	int	i;
	int	len;

	i = 0;
	while (input[i])
	{
		if (input[i + 1] == quote)
			break ;
		input[i] = input[i + 1];
		i++;
	}
	len = i;
	while (input[i])
	{
		input[i] = input[i + 1];
		i++;
	}
	i = len;
	while (input[i])
	{
		input[i] = input[i + 1];
		i++;
	}
	return (len);
}

int	handle_quotes(t_token *tokens)
{
	int	i;

	while (tokens)
	{
		if (!tokens->value)
		{
			tokens = tokens->next;
			continue ;
		}
		i = 0;
		if (ft_strchr(tokens->value, '\'') || ft_strchr(tokens->value, '\"'))
		{
			while (tokens->value[i])
			{
				if (tokens->value[i] == '\'' || tokens->value[i] == '\"')
					i += remove_quotes(tokens->value + i, tokens->value[i]);
				else
					i++;
			}
		}
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}
