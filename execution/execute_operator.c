/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:10:53 by mstepnic          #+#    #+#             */
/*   Updated: 2026/01/20 22:11:47 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <signal.h>

int	execute_pipe(t_data *data, t_ast *ast)
{
	int		pfd[2];
	int		exit_status;
	pid_t	left_pid;
	pid_t	right_pid;

	if (pipe(pfd) == -1)
		return (perror("pipe"), 1);
	left_pid = fork();
	if (left_pid == -1)
		return (perror("fork"), 1);
	if (!left_pid)
		helper(data, ast->data.op.left, pfd, 1);
	right_pid = fork();
	if (right_pid == -1)
		return (perror("fork"), 1);
	if (!right_pid)
		helper(data, ast->data.op.right, pfd, 0);
	close(pfd[0]);
	close(pfd[1]);
	ignore_sigint();
	waitpid(left_pid, &exit_status, 0);
	waitpid(right_pid, &exit_status, 0);
	return (WEXITSTATUS(exit_status));
}

int	execute_fork(t_data *data, t_ast *ast)
{
	pid_t	pid;
	int		exit_status;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (!pid)
	{
		set_up_signals_for_child();
		exit(execute_ast(data, ast));
	}
	ignore_sigint();
	waitpid(pid, &exit_status, 0);
	return (WEXITSTATUS(exit_status));
}

int	execute_and(t_data *data, t_ast *ast)
{
	int		exit_status;
	t_ast	*temp;

	temp = ast->data.op.left;
	if (temp->type == COMMAND
		&& !is_cd_export_unset_exit(temp->data.exec->args[0]))
		exit_status = execute_fork(data, temp);
	else
		exit_status = execute_ast(data, temp);
	if (exit_status == -1)
		return (1);
	if (exit_status)
		return (exit_status);
	temp = ast->data.op.right;
	if (temp->type == COMMAND
		&& !is_cd_export_unset_exit(temp->data.exec->args[0]))
		exit_status = execute_fork(data, temp);
	else
		exit_status = execute_ast(data, temp);
	if (exit_status == -1)
		return (1);
	return (exit_status);
}

int	execute_or(t_data *data, t_ast *ast)
{
	int		exit_status;
	t_ast	*temp;

	temp = ast->data.op.left;
	if (temp->data.op.type == PIPE || (temp->type == COMMAND
			&& !is_cd_export_unset_exit(temp->data.exec->args[0])))
		exit_status = execute_fork(data, ast->data.op.left);
	else
		exit_status = execute_ast(data, ast->data.op.left);
	if (exit_status == -1)
		return (1);
	if (!exit_status)
		return (exit_status);
	temp = ast->data.op.right;
	if (temp->data.op.type == PIPE || (temp->type == COMMAND
			&& !is_cd_export_unset_exit(temp->data.exec->args[0])))
		exit_status = execute_fork(data, ast->data.op.right);
	else
		exit_status = execute_ast(data, ast->data.op.right);
	if (exit_status == -1)
		return (1);
	return (exit_status);
}

int	execute_operator(t_data *data, t_ast *ast)
{
	if (ast->data.op.type == PIPE)
		return (execute_pipe(data, ast));
	else if (ast->data.op.type == AND)
		return (execute_and(data, ast));
	else if (ast->data.op.type == OR)
		return (execute_or(data, ast));
	return (1);
}
