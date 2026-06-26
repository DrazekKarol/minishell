/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:13:09 by dduda             #+#    #+#             */
/*   Updated: 2025/10/13 18:19:45 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bins.h"

int	ft_echo(t_exec *exec)
{
	int	i;

	if (!exec->args[1])
	{
		printf("\n");
		return (EXIT_SUCCESS);
	}
	if (!ft_strncmp(exec->args[1], "-n", 2))
		i = 2;
	else
		i = 1;
	while (exec->args[i])
	{
		printf("%s", exec->args[i]);
		if (exec->args[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strncmp(exec->args[1], "-n", 2))
		printf("\n");
	return (EXIT_SUCCESS);
}
