#ifndef EXECUTE_H
# define EXECUTE_H

# include "../lib/libft/libft.h"
# include "parser.h"
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>

int		exec_base(t_parser_shell base, char ***my_envp,
		t_history *histry_first);

#endif
