/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:09:16 by mstepnic          #+#    #+#             */
/*   Updated: 2026/01/20 22:02:24 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <signal.h>

bool	is_cd_export_unset_exit(char *builtin)
{
	if (!builtin)
		return (false);
	if (!ft_strncmp(builtin, BUILTIN_CD, ft_strlen(BUILTIN_CD))
		|| !ft_strncmp(builtin, BUILTIN_EXPORT, ft_strlen(BUILTIN_EXPORT))
		|| !ft_strncmp(builtin, BUILTIN_UNSET, ft_strlen(BUILTIN_UNSET))
		|| !ft_strncmp(builtin, BUILTIN_EXIT, ft_strlen(BUILTIN_EXIT)))
		return (true);
	return (false);
}

void	free_data(t_data *data)
{
	free_ast(data->ast);
	free_tokens(data->token_list);
	free_envs(data->env_list);
	free(data->input);
}

void	ft_execute_exit(t_data *data, char *err_msg, int exit_code)
{
	if (err_msg)
		ft_putendl_fd(err_msg, STDERR_FILENO);
	else
		ft_putendl_fd("error\n", STDERR_FILENO);
	free_data(data);
	if (err_msg)
		free(err_msg);
	exit(exit_code);
}

char	**split_paths(t_env *env_list)
{
	char	*path_value;
	char	**splited_path;

	path_value = ft_getenv(env_list, "PATH");
	if (!path_value)
		return (NULL);
	splited_path = ft_split(path_value, ':');
	free(path_value);
	return (splited_path);
}

char	*getexec(t_data *data, char *cmd)
{
	char	*temp_cmd;
	char	**path;
	char	*exec;
	int		i;

	path = split_paths(data->env_list);
	if (!path)
		return (ft_strdup(cmd));
	temp_cmd = ft_strjoin("/", cmd);
	if (!temp_cmd)
		return (ft_free_tab(path), NULL);
	i = 0;
	while (path[i])
	{
		exec = ft_strjoin(path[i], temp_cmd);
		if (!exec)
			return (ft_free_tab(path), free(temp_cmd), NULL);
		if (access(exec, F_OK | X_OK) == 0)
			return (ft_free_tab(path), free(temp_cmd), exec);
		free(exec);
		i++;
	}
	ft_free_tab(path);
	free(temp_cmd);
	return (ft_strdup(cmd));
}

void	helper(t_data *data, t_ast *ast, int pfd[2], int in_or_out)
{
	int	exit_status;
	
	set_up_signals_for_child();
	if (!in_or_out)
		dup2(pfd[0], STDIN_FILENO);
	else
		dup2(pfd[1], STDOUT_FILENO);
	close(pfd[0]);
	close(pfd[1]);
	exit_status = execute_ast(data, ast);
	free_data(data);
	exit(exit_status);
}
