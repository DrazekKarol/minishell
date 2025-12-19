/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrazek <kdrazek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:45:07 by mstepnic          #+#    #+#             */
/*   Updated: 2025/12/18 17:18:20 by kdrazek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Clear, small-API redirect and file open helpers. */

#include "execution.h"
#include <fcntl.h>

int	open_last_infile(char **inputs)
{
	int	fd;
	int	i;

	fd = -1;
	i = 0;
	if (!inputs)
		return (-1);
	while (inputs[i])
	{
		if (fd != -1)
			close(fd);
		fd = open(inputs[i], O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd(inputs[i], 2);
			ft_putendl_fd(": No such file or directory", 2);
			return (-1);
		}
		i++;
	}
	return (fd);
}

int	open_last_outfile(char **outputs, int append)
{
	int	fd;
	int	i;

	fd = -1;
	i = 0;
	if (!outputs)
		return (-1);
	while (outputs[i])
	{
		if (fd != -1)
			close(fd);
		if (append)
			fd = open(outputs[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(outputs[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			ft_putstr_fd(outputs[i], 2);
			ft_putendl_fd(": cannot open output", 2);
			return (-1);
		}
		i++;
	}
	return (fd);
}

void	handle_input_redir(t_pipe *pipes, t_exec *exec)
{
	int	fd;

	if (exec->heredoc_limiters && exec->heredoc_limiters[0])
	{
		dup2(pipes->heredoc_pfd[0], STDIN_FILENO);
		close(pipes->heredoc_pfd[0]);
		return ;
	}
	if (exec->input && exec->input[0])
	{
		fd = open_last_infile(exec->input);
		if (fd == -1)
			exit(1);
		dup2(fd, STDIN_FILENO);
		close(fd);
		return ;
	}
	if (exec->is_inpipe)
		dup2(pipes->prev_fd, STDIN_FILENO);
}

void	handle_output_redir(t_pipe *pipes, t_exec *exec)
{
	int	fd;

	if (exec->output && exec->output[0])
	{
		fd = open_last_outfile(exec->output, exec->append_mode);
		if (fd == -1)
			exit(1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		return ;
	}
	if (exec->is_outpipe)
		dup2(pipes->pfd[1], STDOUT_FILENO);
}

void	redirect(t_pipe *pipes, t_exec *exec)
{
	handle_input_redir(pipes, exec);
	handle_output_redir(pipes, exec);
	close_fds(pipes);
}
