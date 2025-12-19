/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrazek <kdrazek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:39:42 by mstepnic          #+#    #+#             */
/*   Updated: 2025/12/19 14:55:09 by kdrazek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <sys/wait.h>

# define BUILTIN_CD "cd"
# define BUILTIN_ECHO "echo"
# define BUILTIN_ENV "env"
# define BUILTIN_EXIT "exit"
# define BUILTIN_EXPORT "export"
# define BUILTIN_PWD "pwd"
# define BUILTIN_UNSET "unset"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_pipe
{
	int				pfd[2];
	int				heredoc_pfd[2];
	int				prev_fd;
	struct s_data	*data;
}	t_pipe;

typedef enum e_token_type
{
	EXEC,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	ARG
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef enum e_exec_type
{
	BUILTIN,
	BINARY
}			t_exec_type;

typedef struct s_exec
{
	pid_t			pid;
	t_exec_type		type;
	char			**args;
	char			**input;
	char			**output;
	int				is_inpipe;
	int				is_outpipe;
	char			**heredoc_limiters;
	int				append_mode;
	struct s_exec	*next;
}	t_exec;

typedef struct s_data
{
	char	**envp;
	t_env	*envs;
	char	*input;
	t_exec	*exec_list;
	int		commands_count;
	int		exit_status;
}	t_data;

#endif
