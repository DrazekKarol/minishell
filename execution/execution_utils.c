/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrazek <kdrazek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:22:05 by mstepnic          #+#    #+#             */
/*   Updated: 2025/12/19 14:19:08 by kdrazek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <sys/stat.h>

int	check_cd_exit_unset_export(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, BUILTIN_CD, ft_strlen(BUILTIN_CD) + 1)
		|| !ft_strncmp(cmd, BUILTIN_EXIT, ft_strlen(BUILTIN_EXIT) + 1)
		|| !ft_strncmp(cmd, BUILTIN_EXPORT, ft_strlen(BUILTIN_EXPORT) + 1)
		|| !ft_strncmp(cmd, BUILTIN_UNSET, ft_strlen(BUILTIN_UNSET) + 1))
		return (1);
	return (0);
}

void	error_and_exit(char *name, char *reason, int code)
{
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(reason, 2);
	exit(code);
}

void	exec_binary(char **args, char **envp)
{
	char		*path_exec;
	struct stat	st;

	if (!args || !args[0])
		exit(0);
	path_exec = getexec(args[0]);
	if (!path_exec)
		error_and_exit(args[0], "Malloc error", 1);
	if (access(path_exec, F_OK) == -1)
		error_and_exit(args[0], "No such file or directory", 127);
	stat(path_exec, &st);
	if (S_ISDIR(st.st_mode))
		error_and_exit(args[0], "Is a directory", 126);
	if (access(path_exec, X_OK) == -1)
		error_and_exit(args[0], "Permission denied", 126);
	if (execve(path_exec, args, envp) == -1)
		error_and_exit(args[0], "command not found", 127);
}

char	*getexec(char *cmd)
{
	char	**paths;
	char	*tmp;
	char	*candidate;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
		return (ft_strdup(cmd));
	tmp = ft_strjoin("/", cmd);
	candidate = find_candidate(paths, tmp);
	ft_free_tab(paths);
	free(tmp);
	if (candidate)
		return (candidate);
	return (ft_strdup(cmd));
}

char	*find_candidate(char **paths, char *tmp)
{
	int		i;
	char	*candidate;

	i = 0;
	while (paths[i])
	{
		candidate = ft_strjoin(paths[i], tmp);
		if (!candidate)
			return (NULL);
		if (access(candidate, F_OK | X_OK) == 0)
			return (candidate);
		free(candidate);
		i++;
	}
	return (NULL);
}
