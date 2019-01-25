#ifndef FT_TERMCAPS_H
# define FT_TERMCAPS_H

# include "../lib/libft/libft.h"
# include <term.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

int		f_putchar(int c);
int		init_termcaps(void);
int		reset_termcaps(void);

#endif
