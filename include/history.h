#ifndef HISTORY_H
# define HISTORY_H

# include "../lib/libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# define PATH_HISTORY ".21sh_history"
# define REMALLOC_HISTORY 1

typedef struct		s_history
{
	int				len_buf;
	int				malloc_buf;
	int				pos_buf;
	int				*len;
	int				*len_malloc;
	int				*pos;
	char			**buf;
}					t_history;

#endif
