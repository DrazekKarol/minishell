/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrazek <kdrazek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:58:42 by mstepnic          #+#    #+#             */
/*   Updated: 2025/11/26 18:55:33 by kdrazek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bins.h"

int	exec_builtin(t_data *data, t_exec *exec)
{
	if (!exec->args || !exec->args[0])
		return (0);
	if (!ft_strncmp(exec->args[0], BUILTIN_ECHO, ft_strlen(BUILTIN_ECHO)))
		return (ft_echo(exec));
	if (!ft_strncmp(exec->args[0], BUILTIN_CD, ft_strlen(BUILTIN_CD)))
		return (ft_cd(data, exec));
	if (!ft_strncmp(exec->args[0], BUILTIN_PWD, ft_strlen(BUILTIN_PWD)))
		return (ft_pwd(data));
	if (!ft_strncmp(exec->args[0], BUILTIN_EXPORT, ft_strlen(BUILTIN_EXPORT)))
		return (ft_export(data, exec));
	if (!ft_strncmp(exec->args[0], BUILTIN_UNSET, ft_strlen(BUILTIN_UNSET)))
		return (ft_unset(data, exec));
	if (!ft_strncmp(exec->args[0], BUILTIN_ENV, ft_strlen(BUILTIN_ENV)))
		return (ft_env(data, exec));
	if (!ft_strncmp(exec->args[0], BUILTIN_EXIT, ft_strlen(BUILTIN_EXIT)))
		return (ft_exit(data, exec));
	ft_putstr_fd("command not found: ", 2);
	ft_putendl_fd(exec->args[0], 2);
	return (127);
}
