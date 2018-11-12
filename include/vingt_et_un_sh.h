#ifndef VINGT_ET_UN_SH_H
# define VINGT_ET_UN_SH_H

# include <stdio.h>
# include "lchar.h"
# include "history.h"

char	**creat_envp(char **true_envp);
int		inport_history(t_history *history);
int		export_history(t_history *history, int error);
int		line_edition(t_history *history);
int		parser(t_lchar *buf);

#endif
