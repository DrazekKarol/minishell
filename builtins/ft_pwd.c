/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:42:14 by mstepnic          #+#    #+#             */
/*   Updated: 2026/01/16 15:53:33 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bins.h"

int	ft_pwd(t_data *data)
{
	char	*pwd;

	pwd = ft_getenv(data->env_list, "PWD");
	if (!pwd)
	{
		printf("\n");
		return (EXIT_FAILURE);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
