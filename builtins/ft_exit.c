/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:25:00 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/13 17:50:26 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bins.h"

int	validate_argument(char *arg)
{
	int	i;

	if (!arg)
		return (EXIT_SUCCESS);
	if (!ft_isdigit(arg[0]) && arg[0] != '+' && arg[0] != '-')
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": numeric argument required", 2);
		return (EXIT_FAILURE);
	}
	i = 1;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putendl_fd(" : numeric argument required", 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_exit(t_data *data, t_exec *exec)
{
	int	exit_status;

	printf("exit\n");
	if (exec->args[1] && exec->args[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (EXIT_FAILURE);
	}
	if (validate_argument(exec->args[1]) == EXIT_FAILURE)
	{
		free_ast(data->ast);
		free_tokens(data->token_list);
		free_envs(data->env_list);
		exit(2);
	}
	exit_status = 0;
	if (exec->args[1])
		exit_status = ft_atoi(exec->args[1]);
	free_ast(data->ast);
	free_tokens(data->token_list);
	free_envs(data->env_list);
	exit(exit_status);
}
