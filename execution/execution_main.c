/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrazek <kdrazek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:40:36 by mstepnic          #+#    #+#             */
/*   Updated: 2025/12/19 15:41:29 by kdrazek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"
#include <errno.h>

int	prepare_heredoc_if_needed(t_pipe *pipes, t_exec *cmd)
{
	int	ret;

	if (!cmd->heredoc_limiters || !cmd->heredoc_limiters[0])
		return (0);
	if (pipe(pipes->heredoc_pfd) == -1)
		return (perror("pipe"), -1);
	ret = feed_heredoc_lines(pipes, cmd);
	close(pipes->heredoc_pfd[1]);
	return (ret);
}

char	*expand_heredoc_line(t_data *data, char *line)
{
	int		i;
	char	*expanded;

	expanded = ft_strdup(line);
	if (!expanded)
		return (NULL);
	i = 0;
	while (expanded[i])
	{
		if (expanded[i] == '$')
		{
			if (extend_env(data, &expanded, 0, &i) == EXIT_FAILURE)
				return (free(expanded), NULL);
			if (!ft_strchr(expanded, '$'))
				break ;
		}
		i++;
	}
	return (expanded);
}

int	feed_heredoc_lines(t_pipe *pipes, t_exec *cmd)
{
	int		i;
	char	*line;

	i = 0;
	while (cmd->heredoc_limiters[i])
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strncmp(line, cmd->heredoc_limiters[i],
				ft_strlen(cmd->heredoc_limiters[i]))
			&& ft_strlen(line) == ft_strlen(cmd->heredoc_limiters[i]))
			return (free(line), i++, 0);
		line = expand_heredoc_line(pipes->data, line);
		if (!line)
			return (-1);
		ft_putendl_fd(line, pipes->heredoc_pfd[1]);
		free(line);
		i++;
	}
	return (0);
}

int	run_exec_loop(t_data *data, t_pipe *pipes)
{
	t_exec	*cur;

	pipes->prev_fd = 0;
	cur = data->exec_list;
	while (cur)
	{
		if (prepare_heredoc_if_needed(pipes, cur) == -1)
			return (-1);
		if (setup_pipe_if_needed(pipes, cur) == -1)
			return (-1);
		if (handle_single_builtin(data, pipes, cur))
			return (0);
		if (spawn_and_setup(data, pipes, cur) == EXIT_FAILURE)
			return (-1);
		parent_after_spawn(pipes, cur);
		cur = cur->next;
	}
	return (0);
}

void	execute(t_data *data)
{
	t_pipe		pipes;

	pipes.data = data;
	pipes.pfd[0] = -1;
	pipes.pfd[1] = -1;
	pipes.heredoc_pfd[0] = -1;
	pipes.heredoc_pfd[1] = -1;
	pipes.prev_fd = -1;
	if (run_exec_loop(data, &pipes) == -1)
		return ;
	if (data->commands_count == 1
		&& data->exec_list
		&& data->exec_list->type == BUILTIN
		&& check_cd_exit_unset_export(data->exec_list->args[0]))
		return ;
	data->exit_status = wait_all_and_collect(data->exec_list);
}
