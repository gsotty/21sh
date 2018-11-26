#ifndef LINE_EDITION_H
# define LINE_EDITION_H

# include "../lib/libft/libft.h"
# include "./lchar.h"
# include <sys/ioctl.h>

# define LEN_REMALLOC 25
# define PROMT (type == 0 ? PROMT_EDIT : PROMT_HER)
# define LEN_PROMT (type == 0 ? LEN_PROMT_EDIT : LEN_PROMT_HER)
# define PROMT_EDIT "$> "
# define LEN_PROMT_EDIT 3
# define PROMT_HER "> "
# define LEN_PROMT_HER 2

typedef struct		s_pos
{
	int				co_max;
	int				li_max;
	int				co_pos;
	int				li_pos;
	int				co_len;
	int				li_len;
}					t_pos;

#endif
