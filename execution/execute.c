/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 18:05:09 by mstepnic          #+#    #+#             */
/*   Updated: 2026/01/20 22:02:40 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <signal.h>

void	error(t_data *data, t_exec *exec, char *executable)
{
	struct stat st;
	
	stat(executable, &st);
	if (S_ISDIR(st.st_mode) && ft_strchr(exec->args[0], '/'))
	{
		free(executable);
		ft_execute_exit(data, ft_strjoin(exec->args[0], ": Is a directory"),
			126);
	}
	if (access(executable, X_OK) == -1 && ft_strchr(exec->args[0], '/'))
	{
		free(executable);
		ft_execute_exit(data, ft_strjoin(exec->args[0], ": Permission denied"),
			126);
	}
	ft_execute_exit(data, ft_strjoin(exec->args[0], ": command not found"),
		127);
}

void	execute_cmd(t_data *data, t_exec *exec)
{
	char		*executable;
	int			exit_status;

	if (exec->type == BINARY)
	{
		executable = getexec(data, exec->args[0]);
		if (!executable)
			ft_execute_exit(data, "Malloc error", 1);
		if (access(executable, F_OK) == -1 && access(executable, X_OK) == -1)
		{
			free(executable);
			ft_execute_exit(data, ft_strjoin(exec->args[0],
					": No such file or directory"), 127);
		}
	}
	if (exec->redirs)
		handle_redirections(data, exec);
	if (exec->type == BUILTIN)
	{
		exit_status = (exec_builtin(data, exec));
		free_data(data);
		exit(exit_status);
	}
	execve(executable, exec->args, envs_to_char_tab(data->env_list));
	error(data, exec, executable);
}

int	execute_subshell(t_data *data, t_ast *ast)
{
	pid_t	pid;
	int		exit_status;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (!pid)
		exit(execute_ast(data, ast->data.subsh));
	waitpid(pid, &exit_status, 0);
	return (WEXITSTATUS(exit_status));
}

int	execute_ast(t_data *data, t_ast *ast)
{
	if (ast->type == OPERATOR)
		return (execute_operator(data, ast));
	else if (ast->type == SUBSHELL)
		return (execute_subshell(data, ast));
	else if (ast->type == COMMAND
		&& ast->data.exec->type == BUILTIN
		&& is_cd_export_unset_exit(ast->data.exec->args[0]))
		return (exec_builtin(data, ast->data.exec));
	else if (ast->type == COMMAND)
		execute_cmd(data, ast->data.exec);
	return (1);
}

void	execute(t_data *data)
{
	pid_t		pid;

	if (data->ast->type == COMMAND
		&& !is_cd_export_unset_exit(data->ast->data.exec->args[0]))
	{
		pid = fork();
		if (pid == -1)
			return (perror("fork"));
		if (!pid)
		{
			set_up_signals_for_child();
			execute_ast(data, data->ast);
		}
		ignore_sigint();
		waitpid(pid, &data->exit_status, 0);
		data->exit_status = WEXITSTATUS(data->exit_status);
	}
	else
		data->exit_status = execute_ast(data, data->ast);
}
