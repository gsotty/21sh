#ifndef EXECUTE_H
# define EXECUTE_H

# include "../lib/libft/libft.h"
# include "vingt_et_un_sh.h"
# include "parser.h"
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>

int		exec_base(t_typecmd ****base, t_process *process, t_lenexec *lenexec,
		t_envp *my_envp, t_history *histry_first);

#endif
