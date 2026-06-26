/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:47:02 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/14 19:06:50 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define BUILTIN_CD "cd"
# define BUILTIN_ECHO "echo"
# define BUILTIN_ENV "env"
# define BUILTIN_EXIT "exit"
# define BUILTIN_EXPORT "export"
# define BUILTIN_PWD "pwd"
# define BUILTIN_UNSET "unset"

// defines for tokens
typedef enum e_token_type
{
	TK_EOF,
	TK_WORD,
	TK_REDIR_IN, // <
	TK_REDIR_OUT, // >
	TK_REDIR_APPEND, // >>
	TK_REDIR_HEREDOC, // <<
	TK_LPARENTHESE,
	TK_RPARENTHESE,
	TK_PIPE,
	TK_AND_OP,
	TK_OR_OP
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

// utils/tokens_utils.c
char	**token_list_to_char_tab(t_token *token_list);
t_token	*token_new(t_token_type type, char *value);
void	add_token_back(t_token **head, t_token *new);
void	add_token_after(t_token *node, t_token *new_token);
void	free_tokens(t_token *head);

// defines for environmental variables
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

// utils/envs_utils1.c
char	*ft_getenv(t_env *envs, char *name);
void	remove_env(t_env **envs, char *name);;
void	add_env(t_env **envs, t_env *new_node);
t_env	*env_new(char *env);
t_env	*create_env_list(char **envp);

// utils/envs_utils2.c
int		env_exists(const char *name, t_env *envs);
void	update_env(t_env *envs, char *name, char *new_value);
void	free_envs(t_env *envs);
char	**envs_to_char_tab(t_env *envs);

// defines for execution structure
typedef enum e_exec_type
{
	BINARY,
	BUILTIN
}	t_exec_type;

typedef struct s_exec
{
	t_exec_type	type;
	char		**args;
	t_token		*redirs;
}	t_exec;

// utils/exec_utils.c
void	free_exec(t_exec *exec);

// defines for abstract syntax tree
# define AND_OR_OP_LBP 1.0
# define AND_OR_OP_RBP 1.1
# define PIPE_OP_LBP 2.0
# define PIPE_OP_RBP 2.1

typedef enum e_node_type
{
	OPERATOR,
	COMMAND,
	SUBSHELL
}	t_node_type;

typedef enum e_op_type
{
	AND,
	OR,
	PIPE,
	UNKNOWN
}	t_op_type;

typedef struct e_ast
{
	t_node_type	type;
	union	u_data
	{
		t_exec			*exec;
		struct e_ast	*subsh;
		struct	s_op
		{
			t_op_type		type;
			struct e_ast	*left;
			struct e_ast	*right;
		}	op;
	}	data;
}	t_ast;

// utils/ast_utils.c
t_ast	*new_cmd_node(t_exec *exec_list);
t_ast	*new_op_node(t_op_type op_type, t_ast *left, t_ast *right);
t_ast	*new_subsh_node(t_ast *subsh);
void	free_ast(t_ast *ast);

// main structure of the program
typedef struct s_data
{
	char	*input;
	t_env	*env_list;
	t_token	*token_list;
	t_ast	*ast;
	int		exit_status;
}	t_data;

#endif