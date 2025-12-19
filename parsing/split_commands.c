/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 19:16:45 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/03 16:34:46 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list	*get_command(char *input, int *i)
{
	t_list	*new_node;
	char	quote;
	int		start;

	start = *i;
	quote = 0;
	while (input[*i])
	{
		if (input[*i] == '\'' || input[*i] == '\"')
		{
			quote = input[*i];
			(*i)++;
			while (input[*i] && input[*i] != quote)
				(*i)++;
			if (input[*i] == quote)
				(*i)++;
			quote = 0;
		}
		else if (!input[*i] || (input[*i] == '|' && !quote))
			break ;
		(*i)++;
	}
	new_node = ft_lstnew(ft_substr(input, start, *i - start));
	return (new_node);
}

t_list	*split_commands(char *input)
{
	t_list	*commands;
	t_list	*new_command;
	int		i;

	if (!ft_strchr(input, '|'))
		return (ft_lstnew(ft_strdup(input)));
	i = 0;
	commands = NULL;
	while (input && input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		new_command = get_command(input, &i);
		if (!new_command)
		{
			ft_lstclear(&commands, free);
			return (NULL);
		}
		ft_lstadd_back(&commands, new_command);
		if (input[i] == '|')
			i++;
	}
	return (commands);
}
