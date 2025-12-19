/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:53:54 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/03 16:22:52 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_for_unclosed_quotes(const char *input)
{
	int	singleq;
	int	doubleq;
	int	i;

	i = 0;
	singleq = 0;
	doubleq = 0;
	while (input[i])
	{
		if (input[i] == '\'' && doubleq % 2 == 0)
			singleq++;
		else if (input[i] == '"' && singleq % 2 == 0)
			doubleq++;
		i++;
	}
	if (singleq % 2 != 0 || doubleq % 2 != 0)
	{
		printf("Error: quotes are not closed!\n");
		return (0);
	}
	return (1);
}

int	validate_input(t_data *data, char *input)
{
	if (!*input)
	{
		data->commands_count = 0;
		data->exec_list = NULL;
		return (EXIT_SUCCESS);
	}
	if (!data || !input || !*input)
		return (EXIT_FAILURE);
	while (*input && ft_isspace(*input))
		input++;
	if (check_for_unexpected_token(input))
	{
		data->exec_list = NULL;
		data->commands_count = 0;
		data->exit_status = 2;
		return (EXIT_FAILURE);
	}
	if (!check_for_unclosed_quotes(input))
	{
		data->exec_list = NULL;
		data->commands_count = 0;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
