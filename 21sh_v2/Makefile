# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsotty <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 15:44:40 by gsotty            #+#    #+#              #
#    Updated: 2017/08/17 15:01:12 by gsotty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

CC = gcc

FLAG = -ltermcap -g -Wall -Wextra -Werror

FLAG_SRC = -c -g -Wall -Wextra -Werror

LIBFT = ./libft

LIBPRINTF = ./ft_printf

INCLUDE = ./vingt_et_un_sh.h

SRC = main.c \
	  add_history.c \
	  clear_win.c \
	  creat_envp.c \
	  creat_history.c \
	  creat_cpy_his.c \
	  cursor_left.c \
	  cursor_move.c \
	  cursor_right.c \
	  delete_character.c \
	  delete_character_2.c \
	  export_history.c \
	  f_putchar.c \
	  find_var_env.c \
	  free_tab.c \
	  ft_strsplit_space.c \
	  historique.c \
	  key_end.c \
	  key_home.c \
	  len_of_nbr_ligne.c \
	  len_tab.c \
	  parser.c \
	  prepare_and_reset_term.c \
	  remalloc_cmd.c \
	  remalloc_history.c \
	  signal.c \
	  write_cmd.c \
	  write_cmd_fontion.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -s -C $(LIBFT) re
	make -s -C $(LIBPRINTF) re
	$(CC) $(FLAG) $(SRC) ./libft/libft.a ./ft_printf/libftprintf.a -o $(NAME)

debug: $(OBJ)
	make -s -C $(LIBFT) re
	make -s -C $(LIBPRINTF) re
	$(CC) -g $(FLAG) $(SRC) ./libft/libft.a ./ft_printf/libftprintf.a -o $(NAME)
	make -s -C $(LIBFT) clean
	make -s -C $(LIBPRINTF) clean
	rm -Rf $(OBJ)

%.o : %.c
	$(CC) $(FLAG_SRC) $<

clean:
	make -C $(LIBFT) clean
	make -s -C $(LIBPRINTF) clean
	rm -Rf $(OBJ)

declean:
	make -C $(LIBFT) fclean
	make -s -C $(LIBPRINTF) fclean
	rm -Rf $(NAME).dSYM
	rm -Rf $(NAME)


fclean: clean
	make -C $(LIBFT) fclean
	make -s -C $(LIBPRINTF) fclean
	rm -Rf $(NAME)

clean_history:
	rm .21sh_history

re: fclean all
