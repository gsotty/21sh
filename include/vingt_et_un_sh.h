#ifndef VINGT_ET_UN_SH_H
# define VINGT_ET_UN_SH_H

# include <stdio.h>
# include "lchar.h"
# include "history.h"

char	**creat_envp(char **true_envp);
int		inport_history(t_history *history);
int		export_history(t_history *history, int error);
int		line_edition(int type, t_history *history);
int		parser(t_lchar *buf, char **my_envp, t_history *history);
void	exec_cmd(int my_argc, char **my_argv, char **my_envp);
int		while_main(int type, t_history *history_first, t_history *history_copy);

#endif
