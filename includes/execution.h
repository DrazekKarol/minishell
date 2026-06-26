/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 18:05:21 by mstepnic          #+#    #+#             */
/*   Updated: 2026/01/20 22:09:20 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <fcntl.h>
# include <stdbool.h>
# include "defines.h"
# include "libft.h"
# include <signals.h>

// execution/execute.c
int		execute_ast(t_data *data, t_ast *ast);

// execution/execute_operator.c
int		execute_operator(t_data *data, t_ast *ast);
int		execute_or(t_data *data, t_ast *ast);
int		execute_and(t_data *data, t_ast *ast);
int		execute_pipe(t_data *data, t_ast *ast);

// execution/redirection_utils.c
void	handle_redirections(t_data *data, t_exec *exec);

// execution/execute_utils.c
bool	is_cd_export_unset_exit(char *builtin);
void	free_data(t_data *data);
void	ft_execute_exit(t_data *data, char *err_msg, int exit_code);
char	*getexec(t_data *data, char *cmd);
void	helper(t_data *data, t_ast *ast, int pfd[2], int in_or_out);

// builtins/execute_builtin.c
int		exec_builtin(t_data *data, t_exec *exec);

#endif