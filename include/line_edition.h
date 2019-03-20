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

typedef struct		s_real_length
{
	int				len;
	int				nbr_line;
	int				*pos_char;
	int				*pos_cursor;
}					t_real_length;

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

	t_real_length	promt;
	t_real_length	buf_pos;
	t_real_length	buf_len;
}					t_pos;

#endif
