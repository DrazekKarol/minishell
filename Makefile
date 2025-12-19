NAME = minishell

LIBFT = libft/libft.a
LIB = -Llibft -lft -lreadline -lcurses

INCLUDES = -Ilibft/includes/ -Iincludes/

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

PARSING = parsing_main extend_envs extend_wildcards extend_utils process_quotes split_commands \
	tokenize tokens_utils parse_tokens parsing_utils input_validation check_syntax
EXECUTION = execution_main execution_utils redirections execution_child execution_helpers
ENVS = envs envs_utils
BUILTINS = exec_builtin ft_echo ft_cd ft_pwd ft_export ft_unset ft_env ft_exit
SIGNALS = signals_main

SRC = $(addsuffix .c, $(addprefix parsing/, $(PARSING))) \
		$(addsuffix .c, $(addprefix execution/, $(EXECUTION))) \
		$(addsuffix .c, $(addprefix envs/, $(ENVS))) \
		$(addsuffix .c, $(addprefix builtins/, $(BUILTINS))) \
		$(addsuffix .c, $(addprefix signals/, $(SIGNALS))) \
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