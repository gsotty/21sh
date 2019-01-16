#ifndef FT_TERMCAPS_H
# define FT_TERMCAPS_H

# include "../lib/libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <termcap.h>
# include <term.h>

int		f_putchar(int c);
int		init_termcaps(void);
int		reset_termcaps(void);

#endif
