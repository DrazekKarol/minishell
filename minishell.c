/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:29:05 by mstepnic          #+#    #+#             */
/*   Updated: 2026/01/20 21:33:33 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_only_spaces(char *str)
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

int	init_data(t_data *data)
{
	extern char	**environ;

	data->env_list = create_env_list(environ);
	if (!data->env_list)
		return (0);
	data->token_list = NULL;
	data->ast = NULL;
	data->exit_status = 0;
	return (1);
}

void	process_input(t_data *data)
{
	add_history(data->input);
	data->token_list = lexer(data);
	if (data->token_list)
	{
		data->ast = parser(data);
		if (data->ast)
			execute(data);
		free_tokens(data->token_list);
		free_ast(data->ast);
	}
	free(data->input);
}

int	main(void)
{
	t_data	data;

	if (!init_data(&data))
		return (1);
	while (1)
	{
		set_up_signals_for_parent();
		data.input = readline("minishit💩$: ");
		if (!data.input)
		{
			free_envs(data.env_list);
			printf("exiting -> [minishit💩$]\n");
			break ;
		}
		if (*data.input && !is_only_spaces(data.input))
			process_input(&data);
	}
	rl_clear_history();
	return (0);
}
