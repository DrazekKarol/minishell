/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrazek <kdrazek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:42:14 by mstepnic          #+#    #+#             */
/*   Updated: 2025/12/19 14:15:01 by kdrazek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bins.h"

int	ft_pwd(t_data *data)
{
	char	buffer[PATH_SIZE];
	char	*pwd;

	(void)data;
	pwd = getcwd(buffer, PATH_SIZE);
	if (!pwd)
	{
		perror("pwd");
		return (EXIT_FAILURE);
	}
	printf("%s\n", pwd);
	return (EXIT_SUCCESS);
}
