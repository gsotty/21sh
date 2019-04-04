NAME = 21sh

CC = gcc

FLAG = -g -Wall -Wextra -Werror

TERMCAP = -ltermcap

LIB = ./lib/libft

INCLUDE =	./include/vingt_et_un_sh.h \
			./include/parser.h \
			./include/envp.h \
			./include/history.h \
			./include/line_edition.h \
			./include/lchar.h \
			./include/ft_termcaps.h \
			./include/execute.h

SRC =	main.c \
		ft_signal.c \
		creat_envp.c \
		inport_history.c \
		export_history.c \
		line_edition.c \
		f_putchar.c \
		init_termcaps.c \
		reset_termcaps.c \
		parser.c \
		which_define.c \
		exec_base.c \
		exec_cmd.c \
		env.c \
		remove_env.c \
		verif_flag_env.c \
		find_var_env.c \
		add_env.c \
		tab_envp.c \
		setenv.c \
		unsetenv.c \
		cd.c \
		echo.c \
		add_pwd.c \
		add_oldpwd.c \
		ft_lchardup.c \
		ft_historycpy.c \
		ft_remallochistory.c \
		ft_freehistory.c \
		ft_addtype.c \
		ft_lcharndup.c \
		ft_lcharsplit.c

OBJ = $(SRC:.c=.o)

VPATH = srcs:srcs/envp:srcs/history:srcs/line_edition:srcs/termcaps:srcs/parser:srcs/execute:srcs/built_int:srcs/lchar

%.o: %.c
		$(CC) -c $(FLAG) $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
		make -s -C $(LIB)
		$(CC) $(FLAG) $^ ./lib/libft/libft.a -o $(NAME) $(TERMCAP)

clean:
		make -s -C $(LIB) clean
		rm -Rf $(OBJ)

fclean: clean
		make -s -C $(LIB) fclean
		rm -Rf $(NAME)

clean_history:
		rm .21sh_history

re: fclean all
