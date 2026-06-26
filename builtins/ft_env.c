/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:20:59 by mstepnic          #+#    #+#             */
/*   Updated: 2026/01/13 15:01:51 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bins.h"

int	ft_env(t_data *data, t_exec *exec)
{
	t_env	*envs;

	if (exec->args[1])
	{
		printf("env: too many arguments\n");
		return (EXIT_FAILURE);
	}
	envs = data->env_list;
	while (envs)
	{
		if (envs->value)
			printf("%s=%s\n", envs->name, envs->value);
		envs = envs->next;
	}
	return (EXIT_SUCCESS);
}
