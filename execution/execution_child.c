/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrazek <kdrazek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 19:30:00 by kdrazek           #+#    #+#             */
/*   Updated: 2025/12/18 17:18:20 by kdrazek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <errno.h>

void	child_execute(t_data *data, t_pipe *pipes, t_exec *cmd)
{
	if (cmd->heredoc_limiters && cmd->heredoc_limiters[0])
	{
		dup2(pipes->heredoc_pfd[0], STDIN_FILENO);
		close(pipes->heredoc_pfd[0]);
	}
	else if (cmd->is_inpipe)
	{
		dup2(pipes->prev_fd, STDIN_FILENO);
		close(pipes->prev_fd);
	}
	if (cmd->is_outpipe)
	{
		dup2(pipes->pfd[1], STDOUT_FILENO);
		close(pipes->pfd[1]);
	}
	redirect(pipes, cmd);
	if (cmd->type == BUILTIN)
		exit(exec_builtin(data, cmd));
	exec_binary(cmd->args, envs_to_char_tab(data->envs));
	exit(EXIT_FAILURE);
}

int	spawn_and_setup(t_data *data, t_pipe *pipes, t_exec *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	cmd->pid = pid;
	if (pid == 0)
		child_execute(data, pipes, cmd);
	return (EXIT_SUCCESS);
}
