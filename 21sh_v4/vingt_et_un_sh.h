/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vingt_et_un_sh.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 13:54:20 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/18 17:25:07 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VINGT_ET_UN_SH_H
# define VINGT_ET_UN_SH_H

/*
** Include
*/

# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <limits.h>
# include <term.h>
# include <stdlib.h>
# include <curses.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>

/*
** Define prompt
*/

# define _PROMPT "\033[36m$>\033[0m "
# define _PROMPT_LEN 3
# define _PROMPT_LEN_WRITE 12
# define _PROMPT_ML "> "
# define _PROMPT_LEN_ML 2
# define _PROMPT_LEN_WRITE_ML 2

/*
** Define du lexer
*/

# define _WORD 1
# define _SEP 2
# define _PIPE 3
# define _ROUT 4
# define _RINT 5
# define _APPROUT 6
# define _HEREDOC 7
# define _OR 8
# define _AND 9
# define _DUP_ROUT 10
# define _DUP_RINT 11
# define _ROUTERR 12
# define _FD 13
# define _DIGIT 14
# define _ARGV 15
# define _SPACE 16
# define _TIRET 17
# define _CMD 18
# define _FILE_NAME 19
# define _NEW_LINE 20

/*
** Define tools
*/

# define LEN_REMALLOC 255
# define LEN_REMAL_LI 2
# define PATH_HISTORY ".21sh_history"
# define MAX_ARGV 1024

/*
** Global pour les signal
*/

sig_atomic_t		g_sig;

/*
** Global pour l'envp
*/

char				**g_envp;

/*
** Structur pour le lexer lchar
*/

typedef struct		s_lchar
{
	char			c;
	int				type;
}					t_lchar;

/*
** Structur pour la commande
*/

typedef struct		s_len_cmd
{
	int				len;
	int				len_malloc;
}					t_len_cmd;

	/*
** Structur pour l'exec
*/

typedef struct		s_cmd
{
	char			*exec;
	char			*argv[MAX_ARGV];
}					t_cmd;

typedef struct		s_redir
{
	char			*file_name;
	int				type;
	int				option;
	int				fd;
	int				digit;
	char			*heredoc;
}					t_redir;

typedef struct		s_pipe
{
	t_cmd			*cmd;
	t_redir			**redir;
}					t_pipe;

typedef struct		s_sep
{
	t_pipe			**pipe;
}					t_sep;

typedef struct		s_exec
{
	t_sep			**sep;
}					t_exec;

/*
** Structur pour l'history
*/

typedef struct		s_history
{
	int				len;
	int				len_malloc;
	t_lchar			**history;
}					t_history;

/*
** Structur pour la positon du curseur
*/

typedef struct		s_pos
{
	int				pos;
	int				nbr_line;
	int				history;
	int				is_quote;
	int				is_dquote;
}					t_pos;

/*
** Structur pour l'edition de ligne
*/

typedef struct		s_line
{
	t_pos			*pos;
	t_history		*history;
}					t_line;

/*
** Prototipe des fonction
*/

int					creat_envp(char **envp);
int					len_tab(char **tableau);
void				free_tab(char **tableau);
int					f_putchar(int c);
int					init_termcaps(void);
int					reset_termcaps(void);
t_lchar				**creat_history(t_history *history);
size_t				ft_strlen_lchar(const t_lchar *s);
t_lchar				*ft_strdup_lchar(const t_lchar *s);
int					remalloc_history(t_history *history);
int					export_history(t_history *history);
t_history			*creat_cpy_history(t_history *history);
int					creat_buf(char *buffer, t_history *history);

#endif
