/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrazek <kdrazek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:40:00 by kdrazek           #+#    #+#             */
/*   Updated: 2025/12/19 15:39:43 by kdrazek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <unistd.h>
#include <stdio.h>

int	setup_pipe_if_needed(t_pipe *pipes, t_exec *cur)
{
	if (cur->is_outpipe)
	{
		if (pipe(pipes->pfd) == -1)
		{
			perror("pipe");
			return (-1);
		}
	}
	return (0);
}

int	handle_single_builtin(t_data *data, t_pipe *pipes, t_exec *cur)
{
	if (data->commands_count == 1 && cur->type == BUILTIN
		&& check_cd_exit_unset_export(cur->args[0]))
	{
		data->exit_status = exec_builtin(data, cur);
		if (pipes->prev_fd)
			close(pipes->prev_fd);
		if (cur->is_outpipe)
		{
			close(pipes->pfd[0]);
			close(pipes->pfd[1]);
		}
		return (1);
	}
	return (0);
}

void	parent_after_spawn(t_pipe *pipes, t_exec *cur)
{
	if (cur->is_outpipe)
	{
		close(pipes->pfd[1]);
		if (pipes->prev_fd)
			close(pipes->prev_fd);
		pipes->prev_fd = pipes->pfd[0];
	}
	if (cur->heredoc_limiters && cur->heredoc_limiters[0])
	{
		if (pipes->heredoc_pfd[0])
			close(pipes->heredoc_pfd[0]);
	}
}

void	close_fds(t_pipe *pipes)
{
	if (pipes->pfd[0] != -1 && pipes->pfd[0] > 0)
		close(pipes->pfd[0]);
	if (pipes->pfd[1] != -1 && pipes->pfd[1] > 0)
		close(pipes->pfd[1]);
	if (pipes->prev_fd != -1 && pipes->prev_fd > 0)
		close(pipes->prev_fd);
}

int	wait_all_and_collect(t_exec *head)
{
	int	status;
	int	last_status;

	last_status = 0;
	while (head)
	{
		if (waitpid(head->pid, &status, 0) != -1)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else
				last_status = 128 + WTERMSIG(status);
		}
		head = head->next;
	}
	return (last_status);
}
