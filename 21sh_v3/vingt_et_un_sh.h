/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vingt_et_un_sh.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 11:57:32 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/14 13:57:47 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VINGT_ET_UN_SH_H
# define VINGT_ET_UN_SH_H

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
**	1er block:
**		_SEP = separateur: {;}
**	2eme block:
**		_PIPE = pipe: {|}
**	3eme block:
**		_ROUTERR = redirection output est erreur: {&>} || {>&} fd = 2 est
**					digit = 1
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

# define _PROMPT "\033[36m$>\033[0m "
# define _PROMPT_LEN 3
# define _PROMPT_LEN_WRITE 12
# define _PROMPT_ML "> "
# define _PROMPT_LEN_ML 2
# define _PROMPT_LEN_WRITE_ML 2

# define LEN_REMALLOC 255
# define PATH_HISTORY ".21sh_history"
# define MAX_ARGV 1024

# define _IS_PIPE 1
# define _IS_ROUT 2
# define _IS_RINT 3
# define _IS_RAPP 4
# define _IS_RAND 5

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
** Global pour les signal
*/

sig_atomic_t		g_sig;

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
**
*/

typedef struct		s_lchar
{
	char			c;
	int				type;
}					t_lchar;

typedef struct		s_nbr_lexer
{
	int				to_sep;
	int				to_pipe;
	int				to_approut;
	int				to_heredoc;
	int				to_rint;
	int				to_rout;
	int				to_routerr;
	int				to_dup_input;
	int				to_dup_output;
	int				to_redir;
}					t_nbr_lexer;

typedef struct		s_cmd_redir
{
	int				type_of_redir;
	int				fd;
	int				digit;
	int				tiret;
	int				pipe;
	char			*file_name;
}					t_cmd_redir;

typedef struct		s_cmd_pipe
{
	t_cmd			cmd;
	t_cmd_redir		**redir;
}					t_cmd_pipe;

typedef struct		s_space
{
	int				x;
	int				cut_space;
	int				start;
}					t_space;

typedef struct		s_redir_token
{
	int				x;
	int				cut_rint;
	int				cut_rout;
	int				start;
	int				type;
}					t_redir_token;

typedef struct		s_appredir
{
	int				x;
	int				cut_approut;
	int				cut_heredoc;
	int				cut_routerr;
	int				cut_dup_input;
	int				cut_dup_output;
	int				start;
	int				type;
}					t_appredir;

typedef struct		s_pipe_token
{
	int				x;
	int				cut_pipe;
	int				start;
	int				type;
}					t_pipe_token;

typedef struct		s_and_or
{
	int				x;
	int				cut_and;
	int				cut_or;
	int				start;
	int				type;
}					t_and_or;

typedef struct		s_token
{
	int				type;
	int				fd;
	char			*str;
	struct s_token	*next;
}					t_token;

typedef struct		s_split
{
	int				j;
	int				x;
}					t_split;

typedef struct		s_struc_envp
{
	int				len;
	char			**envp;
}					t_struc_envp;

typedef struct		s_pos
{
	int				pos;
	int				nbr_line;
	int				history;
	int				is_quote;
	int				is_dquote;
}					t_pos;

typedef struct		s_history
{
	int				len;
	int				len_malloc;
	t_lchar			**history;
}					t_history;

typedef struct		s_len_cmd
{
	int				len;
	int				len_cmd_malloc;
}					t_len_cmd;

typedef struct		s_lexer
{
	t_token			*sep;
	int				first_call_sep;
	t_token			*pipe;
	int				first_call_pipe;
	t_token			*appredir;
	int				first_call_appredir;
	t_token			*redir;
	int				first_call_redir;
	t_token			*space;
	int				first_call_space;
}					t_lexer;

t_lchar				*creat_buf(char *buffer, t_len_cmd *len,
		t_history *history);
t_lchar				*ft_memcpy_lchar(t_lchar *dest, const t_lchar *src, size_t n);
size_t				ft_strlen_lchar(const t_lchar *s);
t_lchar				*ft_strdup_lchar(const t_lchar *s);
t_lchar				**creat_history(t_history *history);
int					add_history(t_history *history, t_lchar *cmd, int len);
void				ft_write_cmd(char *buffer, t_lchar *cmd, t_pos *pos,
		t_len_cmd *len);
void				write_new_cmd(t_lchar *cmd, t_pos *pos, int len);
void				free_tab(char **tableau, int len_tab);
void				free_tab_lchar(t_lchar **tableau, int len_tab);
t_lchar				*remalloc_cmd_lchar(t_len_cmd *len, t_lchar *cmd);
int					parser(t_lchar *cmd, t_len_cmd *len,
		t_struc_envp *struc_envp);
void				clear_win(t_lchar *cmd, t_len_cmd *len, t_pos *pos);
void				del_multi_line(char *buffer, t_lchar *cmd, t_pos *pos,
		t_len_cmd *len);
void				ft_delete_character_2(t_lchar *cmd, t_len_cmd *len,
		t_pos *pos);
void				ft_delete_character(t_lchar *cmd, t_len_cmd *len,
		t_pos *pos);
void				ft_key_end(t_lchar *cmd, t_pos *pos, t_len_cmd *len);
void				ft_key_home(t_lchar *cmd, t_pos *pos, t_len_cmd *len);
t_token				*creat_token_sep(t_lchar *cmd, int len, int first_call);
int					skip_quote_and_backslash(t_lchar *cmd, int len, int *count);



int					exe_tree(t_exec *c, t_nbr_lexer *nbr,
		t_struc_envp *struc_envp);
int					count_nbr_lexer(t_nbr_lexer *nbr, t_token *token);
int					creat_tab_cmd(t_nbr_lexer *nbr, t_exec *c,
		t_token *begin_token);
int					is_type(char *cmd, int nbr_token);
char				*ft_print_type(int x);
t_token				*token_new(void const *content, size_t content_size,
		int nbr_token);
void				token_del(t_token **alst);
t_token				*creat_token_and_or(char *cmd, int len, int first_call);
t_token				*creat_token_pipe(char *cmd, int len, int first_call,
		int type);
t_token				*creat_token_appredir(char *cmd, int len,
		int first_call, int type);
t_token				*creat_token_redir(char *cmd, int len,
		int first_call, int type);
t_token				*creat_token_space(char *cmd, int len, int first_call,
		int type);

char				**creat_envp(char **envp, int len_envp);
int					ctrl_d(t_pos *pos, t_len_cmd *len, t_history *history);
t_history			creat_cpy_history(t_history *history);
void				ft_cursor_left(t_pos *pos, struct winsize win);
int					ft_cursor_move(char *buffer, t_pos *pos, struct winsize win,
		int len);
void				ft_cursor_right(t_pos *pos, struct winsize win, int len);
void				ft_exe(t_cmd *cmd, t_struc_envp *struc_envp);
int					export_history(t_history *history);
int					f_putchar(int c);
char				*find_var_env(char *name, t_struc_envp *struc_envp);
void				*ft_memcpy_modif(void *dest, const void *src, size_t n);
char				**ft_strsplit_space(char const *buf, char *c);
int					history_down(t_pos *pos, t_len_cmd *cmd, t_history *history,
		struct winsize win);
int					history_up(t_pos *pos, t_len_cmd *cmd, t_history *history,
		struct winsize win);
int					key_of_keyboard(char *buffer, t_len_cmd *len, t_pos *pos,
		t_history *history);
int					len_of_nbr_ligne(struct winsize win, int pos);
int					len_tab(char **tableau);
int					prepare_term(void);
int					reset_term(void);
char				*remalloc_cmd(t_len_cmd *len, char *cmd);
int					remalloc_history(t_history *history);
void				ft_signal(void);
void				ft_signal_child(void);
char				***strsplit_to_tab(int len_cmd, char **cmd_tab,
		const char *c);
void				new_safe_place(int len);

#endif
