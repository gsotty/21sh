# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsotty <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 15:44:40 by gsotty            #+#    #+#              #
#    Updated: 2017/08/27 11:20:30 by gsotty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

CC = clang

FLAG = -ltermcap -g -Wall -Wextra -Werror

FLAG_SRC = -c -g -Wall -Wextra -Werror

LIBFT = ./libft

LIBPRINTF = ./ft_printf

INCLUDE = ./vingt_et_un_sh.h

SRC = main.c \
	  clear_win.c \
	  creat_buf.c \
	  ctrl_d.c \
	  cursor_left.c \
	  cursor_move.c \
	  cursor_right.c \
	  del_multi_line.c \
	  delete_character.c \
	  delete_character_2.c \
	  key_end.c \
	  key_home.c \
	  key_of_keyboard.c \
	  creat_envp.c \
	  add_history.c \
	  creat_history.c \
	  creat_cpy_his.c \
	  export_history.c \
	  history_down.c \
	  history_up.c \
	  exe_cmd.c \
	  parser.c \
	  f_putchar.c \
	  find_var_env.c \
	  free_tab.c \
	  ft_memcpy_modif.c \
	  ft_strsplit_space.c \
	  len_of_nbr_ligne.c \
	  len_tab.c \
	  prepare_and_reset_term.c \
	  remalloc_cmd.c \
	  remalloc_history.c \
	  signal.c \
	  strsplit_to_tab.c \
	  write_cmd.c \
	  write_cmd_fontion.c \
	  token_new.c \
	  token_del.c \
	  creat_token.c

OBJ = $(SRC:.c=.o)

VPATH = srcs:srcs/creat_cmd_and_edit_line:srcs/envp:srcs/history:\
	srcs/interpreteur:srcs/parser:srcs/tools

%.o : %.c
	$(CC) $(FLAG_SRC)  $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	make -s -C $(LIBFT)
	make -s -C $(LIBPRINTF)
	$(CC) $(FLAG) $^ ./libft/libft.a ./ft_printf/libftprintf.a -o $(NAME)

clean:
	make -s -C $(LIBFT) clean
	make -s -C $(LIBPRINTF) clean
	rm -Rf $(OBJ)

fclean: clean
	make -s -C $(LIBFT) fclean
	make -s -C $(LIBPRINTF) fclean
	rm -Rf $(NAME)

clean_history:
	rm .21sh_history

re: fclean all
