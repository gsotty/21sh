/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vingt_et_un_sh.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 13:54:20 by gsotty            #+#    #+#             */
/*   Updated: 2017/10/03 15:40:17 by gsotty           ###   ########.fr       */
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
# define _PROMPT "\033[36m$>\033[0m "
*/

# define _PROMPT "bonjour c'est mon shell ^^"
# define _PROMPT_LEN (int)ft_strlen(_PROMPT)
# define _PROMPT_LEN_WRITE (int)ft_strlen(_PROMPT)
# define _PROMPT_ML "> "
# define _PROMPT_LEN_ML 2
# define _PROMPT_LEN_WRITE_ML 2
# define _DEFINE_LEN_P (modif_prompt == 0 ? _PROMPT_LEN : _PROMPT_LEN_ML)

/*
**	1er block:
**		_SEP = separateur: {;}
**	2eme block:
**		_PIPE = pipe: {|}
**	3eme block:
**		_ROUTERR = redirection output est erreur: {&>} || {>&} fd = 2 est
**						digit = 1
**		_DUP_INPUT = dupication input: {[N]<&digit[-]} N de base a 0
**		_DUP_OUTPUT = dupication output: {[N]>&digit[-]} N de base a 1
**		_APPROUT = append redirection output: {[N]>>} N de base a 1
**		_HEREDOC = Here documents: {[N]<<[-]} N de base a 0
**	4eme block:
**		_RINT = redirection input: {[N]<} N de base a 0
**		_ROUT = redirection output: {[N]>[|]} N de base a 1
**	5eme block:
**		_FD = les fd pour les redirection: avant une redirection [*0-9]
**		_FILE = fichier pour les redirection: aprait une redirection
**		_WORD = cmd est argv: c'est les mot restant
**		_SPACE = espace: [ ]
*/

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
# define _NBR 21

/*
** Define tools
*/

# define _LINE line[x].history->history[line[x].pos->history]
# define T_ROTAIT (rotaite_fd == 1 ? pipefd_one : pipefd_tow)
# define T_ROTAIT_INV (rotaite_fd == 1 ? pipefd_tow : pipefd_one)
# define NO_MODIF_PROMPT 0
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

typedef struct		s_define_lchar
{
	int		is_cmd;
	int		is_redir;
	int		is_tiret;
	int		is_digit;
	int		cmd_is_enpli;
}					t_define_lchar;

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
	int				len_heredoc;
}					t_redir;

typedef struct		s_pipe
{
	t_cmd			cmd;
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
** Structur pour le nombre de a allouer pour l'exec
*/

typedef struct		s_len_exec
{
	int				sep;
	int				pipe;
	int				redir;
}					t_len_exec;

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

typedef struct		s_quote
{
	int				is_quote;
	int				is_dquote;
	int				is_backslash;
}					t_quote;

typedef struct		s_pos
{
	int				pos;
	int				len;
	int				len_malloc;
	int				nbr_line;
	int				history;
	int				is_quote;
	int				is_dquote;
	int				is_backslash;
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
** Structur pour le strsplit
*/

typedef struct		s_split
{
	int				j;
	int				x;
}					t_split;

/*
** Structur pour les forck et les redir
*/

typedef struct		s_tab_pid_t
{
	pid_t			*pid_t;
	int				len;
	int				len_malloc;
	int				fd_int;
	int				fd_out;
	int				fd_to_int;
	int				fd_to_out;
	int				heredoc;
}					t_tab_pid_t;

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
t_lchar				*creat_buf(int x, int nbr_line, char *buffer,
		t_history *history);
void				free_tab_lchar(t_lchar **tableau);
t_lchar				*remalloc_cmd_lchar(t_pos *len, t_lchar *cmd);
t_lchar				*ft_memcpy_lchar(t_lchar *dest, const t_lchar *src,
		size_t n);
void				ft_write_cmd(char *buffer, t_lchar *cmd, t_pos *pos,
		int modif_prompt);
void				new_safe_place(int len, int nbr_new_line, int modif_prompt);
int					nbr_new_line(t_lchar *cmd);
void				write_new_cmd(t_lchar *cmd, t_pos *pos, int modif_prompt);
void				clear_win(t_lchar *cmd, t_pos *pos, int modif_prompt);
int					ctrl_d(t_pos *pos, t_history *history, int modif_prompt);
int					len_of_nbr_ligne(struct winsize win, int pos,
		int modif_prompt);
void				ft_delete_character(t_lchar *cmd, t_pos *pos,
		int modif_prompt);
void				ft_delete_character_2(t_lchar *cmd, t_pos *pos,
		int modif_prompt);
void				del_multi_line(char *buffer, t_lchar *cmd, t_pos *pos,
		int modif_prompt);
int					history_down(t_pos *pos, t_history *history,
		struct winsize win, int modif_prompt);
int					history_up(t_pos *pos, t_history *history,
		struct winsize win, int modif_prompt);
void				ft_key_end(t_lchar *cmd, t_pos *pos, int modif_prompt);
void				ft_key_home(t_lchar *cmd, t_pos *pos, int modif_prompt);
int					ft_cursor_move(char *buffer, t_pos *pos,
		struct winsize win, int modif_prompt);
void				ft_cursor_left(t_pos *pos, struct winsize win,
		int modif_prompt);
void				ft_cursor_right(t_pos *pos, struct winsize win,
		int modif_prompt);
int					key_of_keyboard(char *buffer, t_pos *pos,
		t_history *history, int modif_prompt);
void				ft_signal(void);
t_lchar				*free_struct_line(t_line *line, int nbr_line);
t_line				*remalloc_line(t_line *line, t_history *history, int len,
		int new_len);
t_lchar				*end_of_creat_buf(t_line *line, int x, int nbr_line);
int					verif_line(t_quote *quote, t_lchar *cmd);
void				loop_creat_buf(int x, t_line *line, t_quote *quote);
int					add_history(t_history *history, t_lchar *cmd, int len);
int					parser(t_lchar *cmd, int len, t_history *history);
char				*ft_print_type(int x);
int					creat_t_len_exec(t_lchar *cmd, t_len_exec *len_exec);
int					malloc_t_exec(t_lchar *cmd, t_exec *c);
int					creat_tree(t_exec *c, t_lchar *cmd, t_history *history);
int					ft_atoi_lchar(t_lchar *str);
t_lchar				*creat_heredoc(char *eof, int nbr_line, char *buffer,
		t_history *history);
void				new_safe_place_heredoc(int len, int nbr_new_line);
void				ft_write_heredoc(char *buffer, t_lchar *cmd, t_pos *pos);
void				write_new_heredoc(t_lchar *cmd, t_pos *pos);
char				*convert_lchar_to_char(t_lchar *lchar);
int					key_of_keyboard_heredoc(char *buffer, t_pos *pos,
		t_history *history);
int					ft_strcmp_lchar(const t_lchar *s1, const char *s2);
t_lchar				*end_of_creat_buf_heredoc(t_line *line, int x,
		int nbr_line);
char				**ft_strsplit_space(char const *buf, char *c);
char				*find_var_envp(char *name);
void				exec_cmd(t_cmd cmd);
int					exec_tree(t_exec *c);
char				*remalloc_cmd(t_len_cmd *len, char *cmd);
void				close_all(int *pipefd_int, int *pipefd_out);
void				close_tow_fd(int fd1, int fd2);
//int					define_lchar(t_lchar *cmd);

#endif
