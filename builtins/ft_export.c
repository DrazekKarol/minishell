/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrazek <kdrazek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:53:12 by mstepnic          #+#    #+#             */
/*   Updated: 2025/12/15 13:34:24 by kdrazek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bins.h"

int	print_all(t_data *data)
{
	t_env	*envs;

	envs = data->envs;
	while (envs)
	{
		printf("declare -x %s=%s\n", envs->name, envs->value);
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
	char	*ident;

	if (!exec->args[1])
		return (print_all(data));
	ident = ft_substr(exec->args[1], 0,
			ft_strlen_to_char(exec->args[1], '='));
	if (validate_identifier(ident) == EXIT_FAILURE)
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(exec->args[1], 2);
		ft_putendl_fd(" : not a valid identifier", 2);
		return (EXIT_FAILURE);
	}
	if (!ft_strchr(exec->args[1], '='))
		return (EXIT_SUCCESS);
	if (!exec->args[1]
		|| !ft_strncmp(exec->args[1], "=", ft_strlen(exec->args[1])))
		return (EXIT_FAILURE);
	new_node = create_node(exec->args[1]);
	if (!new_node)
		return (EXIT_FAILURE);
	add_env(&data->envs, new_node);
	return (EXIT_SUCCESS);
}
