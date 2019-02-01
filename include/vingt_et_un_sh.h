#ifndef VINGT_ET_UN_SH_H
# define VINGT_ET_UN_SH_H

# include <stdio.h>
# include <signal.h>
# include "lchar.h"
# include "history.h"

/*
** Global pour les signal
*/

typedef	struct		s_envp
{
	char			**envp;
	int				len;
	int				len_malloc;
}					t_envp;

sig_atomic_t		g_sig;

void	ft_signal(int signum, int flags);
int		creat_envp(char **envp, t_envp *my_envp);
int		inport_history(t_history *history);
int		export_history(t_history *history, int error);
int		line_edition(int type, t_history *history);
int		parser(t_lchar *buf, t_envp *my_envp, t_history *history);
void	exec_cmd(int my_argc, char **my_argv, char **my_envp);
int		while_main(int type, t_history *history_first, t_history *history_copy);

#endif
