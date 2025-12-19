/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrazek <kdrazek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:45:21 by mstepnic          #+#    #+#             */
/*   Updated: 2025/12/19 15:39:16 by kdrazek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '\n'
			&& input[i] != '\v' && input[i] != '\r' && input[i] != '\f')
			return (1);
		i++;
	}
	return (0);
}

t_data	init_data(void)
{
	extern char	**environ;
	t_data		data;

	data = (t_data){0};
	data.envp = environ;
	data.exit_status = 0;
	data.envs = create_env_list(data.envp);
	return (data);
}

int	main(void)
{
	t_data			data;

	signals_handler();
	data = init_data();
	run_shell_loop(&data);
	exit(data.exit_status);
	return (0);
}

int	handle_input_once(t_data *data)
{
	data->exec_list = NULL;
	data->input = readline("minishit💩$: ");
	if (!data->input)
	{
		clear_envs(data->envs);
		printf("exiting -> [minishit💩$]\n");
		return (0);
	}
	if (*data->input && check_for_spaces(data->input))
		add_history(data->input);
	if (check_for_spaces(data->input) && parse_input(data) == EXIT_SUCCESS)
		execute(data);
	if (data->exec_list)
		free_exec_list(data->exec_list);
	free(data->input);
	return (1);
}

void	run_shell_loop(t_data *data)
{
	while (1)
	{
		if (!handle_input_once(data))
			break ;
	}
	rl_clear_history();
	rl_cleanup_after_signal();
	if (data->envs)
		clear_envs(data->envs);
	if (data->input)
		free(data->input);
}
