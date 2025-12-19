/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrazek <kdrazek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:25:00 by mstepnic          #+#    #+#             */
/*   Updated: 2025/12/19 14:55:09 by kdrazek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bins.h"

void	free_exec_list_local(t_exec *head)
{
	t_exec	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		if (temp->args)
			ft_free_tab(temp->args);
		if (temp->input)
			ft_free_tab(temp->input);
		if (temp->output)
			ft_free_tab(temp->output);
		if (temp->heredoc_limiters)
			ft_free_tab(temp->heredoc_limiters);
		free(temp);
	}
}

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
		free_exec_list_local(data->exec_list);
		clear_envs(data->envs);
		exit(2);
	}
	exit_status = 0;
	if (exec->args[1])
		exit_status = ft_atoi(exec->args[1]);
	free_exec_list_local(data->exec_list);
	clear_envs(data->envs);
	exit(exit_status);
}
