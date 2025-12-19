# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/29 21:14:44 by mstepnic          #+#    #+#              #
#    Updated: 2025/10/01 16:39:51 by mstepnic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	libft.a

INCLUDES = includes/

FT_IS = alnum alpha ascii digit print space
FT_TO = atoi itoa itoa_base uitoa_base ltoa_base lltoa_base ultoa_base ulltoa_base tolower toupper
FT_MEM = bzero calloc memchr memcmp memcpy memmove memset join_and_free free_tab
FT_STR = split strchr strdup striteri strjoin strlcat strlcpy strlen strmapi strncmp strnstr strrchr strtrim substr
FT_PUT = char endl nbr str
FT_LST = add_back add_front clear delone iter last map new size
FT_MATH = abs nbrlen unbrlen
GNL = get_next_line

SRC = $(addsuffix .c, $(addprefix src/ft_is/ft_is, $(FT_IS))) \
	$(addsuffix .c, $(addprefix src/ft_to/ft_, $(FT_TO))) \
	$(addsuffix .c, $(addprefix src/ft_mem/ft_, $(FT_MEM))) \
	$(addsuffix .c, $(addprefix src/ft_str/ft_, $(FT_STR))) \
	$(addsuffix _fd.c, $(addprefix src/ft_put/ft_put, $(FT_PUT))) \
	$(addsuffix .c, $(addprefix src/ft_lst/ft_lst, $(FT_LST))) \
	$(addsuffix .c, $(addprefix src/ft_math/ft_, $(FT_MATH))) \
	$(addsuffix .c, $(addprefix get_next_line/, $(GNL))) \

OBJ = ${SRC:.c=.o}

CC = cc
AR = ar rcs
CFLAGS = -Wall -Werror -Wextra -c
RM = rm -rf

all: $(NAME)
	mv $(NAME) ft_printf/
	make -C ft_printf/
	mv ft_printf/libft.a .
	
$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@ -I $(INCLUDES)

clean:
	$(RM) $(OBJ)
	make clean -C ft_printf/

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
