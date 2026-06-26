/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:53:12 by mstepnic          #+#    #+#             */
/*   Updated: 2026/01/13 15:02:20 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bins.h"

int	print_all(t_data *data)
{
	t_env	*envs;

	envs = data->env_list;
	while (envs)
	{
		if (envs->value)
			printf("declare -x %s=\"%s\"\n", envs->name, envs->value);
		else
			printf("declare -x %s\n", envs->name);
		envs = envs->next;
	}
	return (EXIT_SUCCESS);
}

int	validate_identifier(char *identifier)
{
	int	i;

	if (*identifier != '_' && !ft_isalpha(*identifier))
		return (EXIT_FAILURE);
	i = 1;
	while (identifier[i])
	{
		if (!ft_isalnum(identifier[i]) && identifier[i] != '_')
			return (EXIT_FAILURE);
		i++;
	}
	free(identifier);
	return (EXIT_SUCCESS);
}

int	ft_export(t_data *data, t_exec *exec)
{
	t_env	*new_node;

	if (!exec->args[1])
		return (print_all(data));
	if (validate_identifier(ft_substr(exec->args[1], 0,
				ft_strlen_to_char(exec->args[1],
					'='))) == EXIT_FAILURE)
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(exec->args[1], 2);
		ft_putendl_fd(" : not a valid identifier", 2);
		return (EXIT_FAILURE);
	}
	new_node = env_new(exec->args[1]);
	if (!new_node)
		return (EXIT_FAILURE);
	add_env(&data->env_list, new_node);
	return (EXIT_SUCCESS);
}
