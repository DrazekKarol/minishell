/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrazek <kdrazek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:14:44 by mstepnic          #+#    #+#             */
/*   Updated: 2025/12/15 13:31:34 by kdrazek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bins.h"
#include <stdio.h>

void	update_pwd(t_data *data, char *old_pwd, char *new_pwd)
{
	t_env	*env;

	env = data->envs;
	while (env)
	{
		if (ft_strncmp(env->name, "OLDPWD", 6) == 0)
		{
			free(env->value);
			env->value = old_pwd;
		}
		else if (ft_strncmp(env->name, "PWD", 3) == 0)
		{
			free(env->value);
			env->value = new_pwd;
		}
		env = env->next;
	}
}

int	change_directory(t_data *data, t_exec *exec)
{
	if (!exec->args[1])
	{
		if (chdir(ft_getenv(data->envs, "HOME")) == -1)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (EXIT_FAILURE);
		}
	}
	else if (chdir(exec->args[1]) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(exec->args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_cd(t_data *data, t_exec *exec)
{
	char	buffer[PATH_SIZE];
	char	*old_pwd;
	char	*new_pwd;

	if (exec->args[1] && exec->args[2])
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (EXIT_FAILURE);
	}
	old_pwd = ft_strdup(getcwd(buffer, PATH_SIZE));
	if (change_directory(data, exec) == EXIT_FAILURE)
		return (free(old_pwd), EXIT_FAILURE);
	new_pwd = ft_strdup(getcwd(buffer, PATH_SIZE));
	update_pwd(data, old_pwd, new_pwd);
	return (EXIT_SUCCESS);
}
