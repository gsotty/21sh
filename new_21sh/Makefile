NAME = 21sh

CC = clang

FLAG = -g -Wall -Wextra -Werror

TERMCAP = -ltermcap

LIB = ./lib/libft

INCLUDE =	./include/vingt_et_un_sh.h \
			./include/envp.h \
			./include/history.h \
			./include/line_edition.h \
			./include/lchar.h \
			./include/ft_termcaps.h \
			./include/parser.h

SRC =	main.c \
		creat_envp.c \
		inport_history.c \
		export_history.c \
		line_edition.c \
		f_putchar.c \
		init_termcaps.c \
		reset_termcaps.c \
		parser.c

OBJ = $(SRC:.c=.o)

VPATH = srcs:srcs/envp:srcs/history:srcs/line_edition:srcs/termcaps:srcs/parser

%.o: %.c
		$(CC) -c $(FLAG) $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
		make -s -C $(LIB)
		$(CC) $(TERMCAP) $(FLAG) $^ ./lib/libft/libft.a -o $(NAME)

clean:
		make -s -C $(LIB) clean
		rm -Rf $(OBJ)

fclean: clean
		make -s -C $(LIB) fclean
		rm -Rf $(NAME)

clean_history:
		rm .21sh_history

re: fclean all
