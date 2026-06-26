# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/19 14:59:23 by mstepnic          #+#    #+#              #
#    Updated: 2025/01/17 19:18:43 by mstepnic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FILES = printf printf_utils flags_utils print_chars print_nbrs print_nbrs_utils

SRC = $(addsuffix .c, $(addprefix src/ft_, $(FILES)))

OBJ = ${SRC:.c=.o}

CC = cc
CFLAGS = -Wall -Werror -Wextra -c
INCLUDES = -I ../includes/
AR = ar rcs
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	$(RM) $(OBJ)