/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrazek <kdrazek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+  +:+       +#+        */
/*   Created: 2025/11/17 00:00:00 by kdrazek           #+#    #+#             */
/*   Updated: 2025/11/17 00:00:00 by kdrazek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "defines.h"
# include "libft.h"
# include "envs.h"
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

char	*getexec(char *cmd);
void	exec_binary(char **args, char **envp);
int		exec_builtin(t_data *data, t_exec *exec);
void	redirect(t_pipe *pipes, t_exec *exec);
void	close_fds(t_pipe *pipes);
int		check_cd_exit_unset_export(char *cmd);
void	execute(t_data *data);
int		setup_pipe_if_needed(t_pipe *pipes, t_exec *cur);
int		handle_single_builtin(t_data *data, t_pipe *pipes, t_exec *cur);
void	parent_after_spawn(t_pipe *pipes, t_exec *cur);
int		wait_all_and_collect(t_exec *head);
int		spawn_and_setup(t_data *data, t_pipe *pipes, t_exec *cmd);
int		prepare_heredoc_if_needed(t_pipe *pipes, t_exec *cmd);
int		feed_heredoc_lines(t_pipe *pipes, t_exec *cmd);
int		run_exec_loop(t_data *data, t_pipe *pipes);
void	error_and_exit(char *name, char *reason, int code);
char	*find_candidate(char **paths, char *tmp);
void	child_execute(t_data *data, t_pipe *pipes, t_exec *cmd);
int		open_last_infile(char **inputs);
int		open_last_outfile(char **outputs, int append);
void	handle_input_redir(t_pipe *pipes, t_exec *exec);
void	handle_output_redir(t_pipe *pipes, t_exec *exec);

#endif
