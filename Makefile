# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsotty <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 15:44:40 by gsotty            #+#    #+#              #
#    Updated: 2017/05/21 12:18:14 by gsotty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

CC = gcc

FLAG = -Wall -Wextra -Werror

LIBFT = ./libft

INCLUDE = ./21sh.h

SRC = main.c \
	  term.c \
	  vingt_et_un_sh.c \
	  f_putchar.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -s -C $(LIBFT) re
	$(CC) -lncurses $(FLAG) $(SRC) ./libft/libft.a -o $(NAME)

debug: $(OBJ)
	make -s -C $(LIBFT) re
	$(CC) -lncurses -g $(FLAG) $(SRC) ./libft/libft.a -o $(NAME)
	make -s -C $(LIBFT) clean
	rm -Rf $(OBJ)

%.o : %.c
	$(CC) $(FLAG) -g -c $<

clean:
	make -C $(LIBFT) clean
	rm -Rf $(OBJ)

declean:
	make -C $(LIBFT) fclean
	rm -Rf $(NAME).dSYM
	rm -Rf $(NAME)


fclean: clean
	make -C $(LIBFT) fclean
	rm -Rf $(NAME)

re: fclean all
