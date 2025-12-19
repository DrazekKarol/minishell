/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrazek <kdrazek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:20:59 by mstepnic          #+#    #+#             */
/*   Updated: 2025/11/26 18:55:33 by kdrazek          ###   ########.fr       */
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
	envs = data->envs;
	while (envs)
	{
		printf("%s=%s\n", envs->name, envs->value);
		envs = envs->next;
	}
	return (EXIT_SUCCESS);
}
