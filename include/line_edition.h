#ifndef LINE_EDITION_H
# define LINE_EDITION_H

# include "../lib/libft/libft.h"
# include "./lchar.h"
# include <sys/ioctl.h>

# define LEN_REMALLOC 25
# define PROMT promt[type].str
# define LEN_PROMT promt[type].len
# define PROMT_EDIT "$> "
# define LEN_PROMT_EDIT 3
# define PROMT_HER "> "
# define LEN_PROMT_HER 2

typedef struct		s_promt
{
	int				len;
	char			*str;
}					t_promt;

typedef struct		s_int_keyboard
{
	int				ret;
	int				sequence[4];
}					t_int_keyboard;

typedef struct		s_calcul_len
{
	int				co_max;
	int				len_tab;

	int				start_char;
	int				start_cursor;
	int				count;
	int				rest;

	int				len_promt;
	int				real_promt;

	int				real;
	int				len;
	int				nbr_char;
	int				nbr_cursor;
}					t_calcul_len;

typedef struct		s_length
{
	int				*pos_char;
	int				*pos_cursor;
}					t_length;

typedef struct		s_pos
{
	int				co_max;
	int				li_max;
	int				len_tab;
	int				start;
	int				end;
	int				nbr_line_pos;
	int				nbr_line_len;

	int				malloc;

	int				nbr_char;
	int				nbr_cursor;
	int				len;
	int				len_promt;
	int				nbr_pos;
	int				char_pos;
	int				cursor_pos;
	t_length		*promt;
	t_length		*buf;


	int				nbr_mx;
	int				nbr_po;
	char			*promt_c;
	char			*promt_r;
	char			*buf_c;
	char			*buf_r;
}					t_pos;

#endif
