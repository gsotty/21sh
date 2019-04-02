#ifndef VINGT_ET_UN_SH_H
# define VINGT_ET_UN_SH_H

# include <stdio.h>
# include <signal.h>
# include "lchar.h"
# include "history.h"
# include <ncurses.h>

# define NAME_TERM "21sh"
# define LEN_NAME_TERM 4

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

void		ft_signal(int signum, int flags);
int			creat_envp(char **envp, t_envp *my_envp);
int			inport_history(t_history *history);
int			export_history(t_history *history, int error);
t_lchar		*line_edition(int type, t_history *history);
int			parser(t_lchar *buf, t_history *history, t_envp *my_envp);
void		exec_cmd(int my_argc, char **my_argv, char **my_envp);
t_lchar		*while_main(int type, t_history *history_first);
t_history	*add_new_history(t_history *history, t_lchar *buf);
int			ft_strmatch(char *str1, char *str2);

#endif
