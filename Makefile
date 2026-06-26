NAME = minishell

LIBFT = libft/libft.a
LIB = -Llibft -lft -lreadline -lcurses

INCLUDES = -Ilibft/includes/ -Iincludes/

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

LEXER = lexer
PARSER = parser extend_envs extend_wildcards process_quotes validate \
		extend_utils parser_utils1 parser_utils2 parser_utils3
EXECUTION = execute execute_operator redirections_utils execute_utils
BUILTINS = execute_builtin ft_cd ft_echo ft_env ft_exit ft_export ft_pwd ft_unset
SIGNALS = signals
UTILS = tokens_utils envs_utils1 envs_utils2 ast_utils exec_utils

SRC = $(addsuffix .c, $(addprefix lexer/, $(LEXER))) \
		$(addsuffix .c, $(addprefix parser/, $(PARSER))) \
		$(addsuffix .c, $(addprefix execution/, $(EXECUTION))) \
		$(addsuffix .c, $(addprefix builtins/, $(BUILTINS))) \
		$(addsuffix .c, $(addprefix signals/, $(SIGNALS))) \
		$(addsuffix .c, $(addprefix utils/, $(UTILS))) \
		minishell.c

OBJ = ${SRC:.c=.o}

all: $(NAME)

$(NAME): $(OBJ) | $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) $(LIB) -o $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

$(LIBFT):
	make -C libft/

clean:
	make clean -C libft/
	$(RM) $(OBJ)

fclean: clean
	make fclean -C libft/
	$(RM) $(NAME)

re: fclean all
