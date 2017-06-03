# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsotty <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 15:44:40 by gsotty            #+#    #+#              #
#    Updated: 2017/06/03 13:51:55 by gsotty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= 21sh
CC				= gcc
CFLAG			= -Wall -Wextra -Werror
LIBFT			= -Llibft -lft
LIBFT_PATH		= ./libft
INC_DIR			= includes/

SRCS			= \
				  main.c \
				  term.c \
				  vingt_et_un_sh.c \
				  f_putchar.c

BUILTIN			= \
				  add_env.c \
				  add_oldpwd.c \
				  add_pwd.c \
				  cd.c \
				  echo.c \
				  env.c \
				  find_var_env.c \
				  free_tab.c \
				  remove_env.c \
				  setenv.c \
				  tab_envp.c \
				  unsetenv.c \
				  verif_flag_env.c \
				  exe_fork.c

PARSING			= \
				  parser.c

TOOLS			= \
				  f_putchar.c \
				  ft_strsplit_space.c

SRCS_OBJ		= $(SRCS:.c=.o)
BUILTIN_OBJ		= $(BUILTIN:.c=.o)
PARSING_OBJ		= $(PARSING:.c=.o)
TOOLS_OBJ		= $(TOOLS:.c=.o)
VPATH			= srcs:srcs/builtin:srcs/parsing:srcs/tools

%.o : %.c
		$(CC) $(FLAG) -g -c $<

all: $(NAME)

$(NAME): $(SRCS_OBJ) $(BUILTIN_OBJ) $(PARSING_OBJ) $(TOOLS_OBJ)
	make -s -C $(LIBFT_PATH)
	$(CC) -ltermcap $(CFLAG) $^ -I $(INC_DIR) $(LIBFT) -o $(NAME)

debug: $(SRCS_OBJ) $(BUILTIN_OBJ) $(PARSING_OBJ) $(TOOLS_OBJ)
	make -s -C $(LIBFT_PATH)
	$(CC) -ltermcap -g $(CFLAG) $^ -I $(INC_DIR) $(LIBFT) -o $(NAME)
	make -s -C $(LIBFT_PATH) clean
	rm -f $(SRCS_OBJ) $(BUILTIN_OBJ) $(PARSING_OBJ) $(TOOLS_OBJ)

clean:
	make -C $(LIBFT_PATH) clean
	rm -f $(SRCS_OBJ) $(BUILTIN_OBJ) $(PARSING_OBJ) $(TOOLS_OBJ)
	rm -f $(OBJ)

declean:
	make -C $(LIBFT_PATH) fclean
	rm -Rf $(NAME).dSYM
	rm -Rf $(NAME)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -Rf $(NAME)

re: fclean all

.PHONY: clean fclean re libft
