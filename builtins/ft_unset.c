/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:16:13 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/13 17:50:49 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bins.h"

int	ft_unset(t_data *data, t_exec *exec)
{
	int	i;

	if (!exec->args[1])
		return (EXIT_SUCCESS);
	i = 1;
	while (exec->args[i])
	{
		remove_env(&data->env_list, exec->args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
