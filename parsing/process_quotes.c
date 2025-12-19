/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:48:33 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/03 15:52:45 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

void	process_quotes(t_token *tokens)
{
	int	i;

	while (tokens)
	{
		i = 0;
		while (tokens->value[i])
		{
			if (tokens->value[i] == '\'' || tokens->value[i] == '\"')
				i += remove_quotes(tokens->value + i, tokens->value[i]);
			else
				i++;
		}
		tokens = tokens->next;
	}
}
