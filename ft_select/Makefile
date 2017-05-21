# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsotty <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 15:44:40 by gsotty            #+#    #+#              #
#    Updated: 2017/05/19 15:04:33 by gsotty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select

CC = gcc

FLAG = -Wall -Wextra -Werror

LIBFT = ./libft

INCLUDE = ./ft_select.h

SRC = delete_bar.c \
	  f_putchar.c \
	  fleche_directionnelle.c \
	  ft_print_argv.c \
	  main.c \
	  read_ft_select.c \
	  return_bar.c \
	  signal.c \
	  space_bar.c \
	  term.c \
	  print_argv.c \
	  ft_exit.c \
	  free_buf.c \
	  all_select.c

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
