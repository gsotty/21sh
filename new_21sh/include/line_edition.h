#ifndef LINE_EDITION_H
# define LINE_EDITION_H

# include "../lib/libft/libft.h"
# include "./lchar.h"
# include <sys/ioctl.h>

# define LEN_REMALLOC 25
# define PROMT "$> "
# define LEN_PROMT 3

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
