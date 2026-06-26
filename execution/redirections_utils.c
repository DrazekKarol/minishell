/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:13:41 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/14 16:50:51 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	handle_heredoc(t_token *redir)
{
	int		heredoc_pfd[2];
	char	*input;

	if (pipe(heredoc_pfd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	while (1)
	{
		input = readline("> ");
		if (!input || !ft_strncmp(input, redir->value,
				ft_strlen(redir->value)))
			break ;
		if (!redir->next)
			ft_putendl_fd(input, heredoc_pfd[1]);
		free(input);
	}
	free(input);
	close(heredoc_pfd[1]);
	return (heredoc_pfd[0]);
}

int	redirect_input(t_data *data, t_token *redir)
{
	int		fd;

	fd = 0;
	if (redir->type == TK_REDIR_IN)
	{
		fd = open(redir->value, O_RDONLY);
		if (fd == -1)
			ft_execute_exit(data, ft_strjoin(redir->value,
					": No such file or directory"), 1);
	}
	else if (redir->type == TK_REDIR_HEREDOC)
		fd = handle_heredoc(redir);
	return (fd);
}

int	redirect_output(t_data *data, t_token *redir)
{
	int		fd;

	fd = 0;
	if (redir->type == TK_REDIR_OUT)
		fd = open(redir->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(redir->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		ft_execute_exit(data,
			ft_strjoin(redir->value, ": couldn't create\n"), 1);
	return (fd);
}

void	redirect(int fd_in, int fd_out)
{
	if (fd_in)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

void	handle_redirections(t_data *data, t_exec *exec)
{
	t_token	*redirs;
	int		fd_in;
	int		fd_out;

	fd_in = 0;
	fd_out = 0;
	redirs = exec->redirs;
	while (redirs)
	{
		if (fd_in && (redirs->type == TK_REDIR_IN
				|| redirs->type == TK_REDIR_HEREDOC))
			close(fd_in);
		if (fd_out && (redirs->type == TK_REDIR_OUT
				|| redirs->type == TK_REDIR_APPEND))
			close(fd_out);
		if (redirs->type == TK_REDIR_IN || redirs->type == TK_REDIR_HEREDOC)
			fd_in = redirect_input(data, redirs);
		else if (redirs->type == TK_REDIR_OUT
			|| redirs->type == TK_REDIR_APPEND)
			fd_out = redirect_output(data, redirs);
		redirs = redirs->next;
	}
	redirect(fd_in, fd_out);
}
