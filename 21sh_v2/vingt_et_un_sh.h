/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vingt_et_un_sh.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 11:57:32 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/27 13:01:31 by gsotty           ###   ########.fr       */
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

# define LEN_REMALLOC 100
# define PATH_HISTORY ".21sh_history"

# define _WORD 1
# define _ASSIGNEMENT_WORD 2
# define _NAME 3
# define _NEWLINE 4
# define _IO_NUMBER 5

# define _LESS 6
# define _GREAT 7
# define _DLESS 8
# define _DGREAT 9
# define _DUP_OUTPUT 10
# define _DUP_INPUT 11
# define _PIPE 12
# define _SEP 13

# define _EOF 14
# define _EOL 15

sig_atomic_t		g_sig;

typedef struct		s_token
{
	int				type;
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
}					t_pos;

typedef struct		s_history
{
	int				len;
	int				len_malloc;
	char			**history;
}					t_history;

typedef struct		s_len_cmd
{
	int				len;
	int				len_cmd_malloc;
}					t_len_cmd;

typedef struct		s_lexer
{
	t_token			*sep;
	t_token			*pipe;
}					t_lexer;

t_token				*token_new(void const *content, size_t content_size,
		int nbr_token);
void				token_del(t_token **alst);
t_token				*creat_token(char *cmd, int len, char *delim,
int first_call);
t_token				*creat_token_2(char *cmd, int len, char *delim,
int first_call);

int					add_history(t_history *history, char *cmd, int len);
void				clear_win(char *cmd, t_len_cmd *len, t_pos *pos);
char				*creat_buf(char *buffer, t_len_cmd *len,
		t_history *history);
char				**creat_envp(char **envp, int len_envp);
char				**creat_history(t_history *history);
int					ctrl_d(t_pos *pos, t_len_cmd *len, t_history *history);
t_history			creat_cpy_history(t_history *history);
void				ft_cursor_left(t_pos *pos, struct winsize win);
int					ft_cursor_move(char *buffer, t_pos *pos, struct winsize win,
		int len);
void				ft_cursor_right(t_pos *pos, struct winsize win, int len);
void				del_multi_line(char *buffer, char *cmd, t_pos *pos,
		t_len_cmd *len);
void				ft_delete_character(char *cmd, t_len_cmd *len,
		t_pos *pos);
void				ft_delete_character_2(char *cmd, t_len_cmd *len,
		t_pos *pos);
void				ft_exe(char **tab_cmd, t_struc_envp *struc_envp);
int					export_history(t_history *history);
int					f_putchar(int c);
char				*find_var_env(char *name, t_struc_envp *struc_envp);
void				free_tab(char **tableau, int len_tab);
void				*ft_memcpy_modif(void *dest, const void *src, size_t n);
char				**ft_strsplit_space(char const *buf, char *c);
int					history_down(t_pos *pos, t_len_cmd *cmd, t_history *history,
		struct winsize win);
int					history_up(t_pos *pos, t_len_cmd *cmd, t_history *history,
		struct winsize win);
void				ft_key_end(char *cmd, t_pos *pos, t_len_cmd *len);
void				ft_key_home(char *cmd, t_pos *pos, t_len_cmd *len);
int					key_of_keyboard(char *buffer, t_len_cmd *len, t_pos *pos,
		t_history *history);
int					len_of_nbr_ligne(struct winsize win, int pos);
int					len_tab(char **tableau);
int					parser(char *cmd, t_len_cmd *len, t_struc_envp *struc_envp);
int					prepare_term(void);
int					reset_term(void);
char				*remalloc_cmd(t_len_cmd *len, char *cmd);
int					remalloc_history(t_history *history);
void				ft_signal(void);
void				ft_signal_child(void);
char				***strsplit_to_tab(int len_cmd, char **cmd_tab,
		const char *c);
void				ft_write_cmd(char *buffer, char *cmd, t_pos *pos,
		t_len_cmd *len);
void				new_safe_place(int len);
void				write_new_cmd(char *cmd, t_pos *pos, int len);

#endif
