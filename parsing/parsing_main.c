/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:18:35 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/05 09:34:53 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parse_commands(t_data *data, t_list *commands)
{
	t_token	*tokens;
	t_exec	*exec_list;
	int		cmd_index;

	exec_list = data->exec_list;
	cmd_index = 0;
	while (commands)
	{
		tokens = tokenize_input((char *)commands->content);
		if (!tokens)
			return (EXIT_FAILURE);
		if (handle_envs(data, tokens) == EXIT_FAILURE)
			return (free_tokens(tokens), EXIT_FAILURE);
		handle_wildcards(tokens);
		process_quotes(tokens);
		if (parse_tokens(data, exec_list, tokens, cmd_index) == EXIT_FAILURE)
			return (free_tokens(tokens), EXIT_FAILURE);
		free_tokens(tokens);
		exec_list = exec_list->next;
		commands = commands->next;
		cmd_index++;
	}
	return (EXIT_SUCCESS);
}

int	parse_input(t_data *data)
{
	t_list	*commands;

	if (validate_input(data, data->input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	commands = split_commands(data->input);
	if (!commands)
		return (EXIT_FAILURE);
	data->commands_count = ft_lstsize(commands);
	data->exec_list = create_exec_list(data->commands_count);
	if (!data->exec_list)
		return (ft_lstclear(&commands, free), EXIT_FAILURE);
	if (parse_commands(data, commands) == EXIT_FAILURE)
		return (ft_lstclear(&commands, free), EXIT_FAILURE);
	ft_lstclear(&commands, free);
	return (EXIT_SUCCESS);
}
