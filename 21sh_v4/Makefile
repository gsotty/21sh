# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsotty <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 15:44:40 by gsotty            #+#    #+#              #
#    Updated: 2017/09/25 17:09:02 by gsotty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

CC = gcc

FLAG = -ltermcap -g -Wall -Wextra -Werror # -fsanitize=address

FLAG_SRC = -c -g -Wall -Wextra -Werror # -fsanitize=address

LIBFT = ./libft

LIBPRINTF = ./ft_printf

INCLUDE = ./vingt_et_un_sh.h

SRC = main.c \
	  creat_envp.c \
	  len_tab.c \
	  free_tab.c \
	  init_termcaps.c \
	  reset_termcaps.c \
	  f_putchar.c \
	  creat_history.c \
	  ft_strlen_lchar.c \
	  ft_strdup_lchar.c \
	  remalloc_history.c \
	  export_history.c \
	  creat_cpy_history.c \
	  creat_buf.c \
	  free_tab_lchar.c \
	  remalloc_cmd_lchar.c \
	  ft_memcpy_lchar.c \
	  write_cmd.c \
	  write_cmd_fonction.c \
	  nbr_new_line.c \
	  clear_win.c \
	  len_of_nbr_ligne.c \
	  delete_character.c \
	  delete_character_2.c \
	  del_multi_line.c \
	  history_down.c \
	  history_up.c \
	  key_end.c \
	  key_home.c \
	  cursor_move.c \
	  cursor_left.c \
	  cursor_right.c \
	  key_of_keyboard.c \
	  ctrl_d.c \
	  signal.c \
	  free_struct_line.c \
	  remalloc_line.c \
	  creat_cmd.c \
	  verif_line.c \
	  loop_creat_buf.c \
	  add_history.c \
	  parser.c \
	  ft_print_type.c \
	  creat_t_len_exec.c \
	  malloc_t_exec.c \
	  creat_tree.c

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
