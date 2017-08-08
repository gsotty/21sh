/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vingt_et_un_sh.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 11:57:32 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/08 15:51:34 by gsotty           ###   ########.fr       */
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

sig_atomic_t	g_sig;

typedef struct	s_split
{
	int			j;
	int			x;
}				t_split;

typedef struct	s_struc_envp
{
	char		**envp;
	int			len;
}				t_struc_envp;

typedef struct	s_pos
{
	int			pos;
	int			nbr_line;
}				t_pos;

typedef struct	s_len_cmd
{
	int			len;
	int			len_cmd_malloc;
}				t_len_cmd;

void			clear_win(char *cmd, t_len_cmd *len, t_pos *pos);
char			**creat_envp(char **envp, int len_envp);
void			ft_cursor_left(t_pos *pos, struct winsize win);
int				ft_cursor_move(char *buffer, t_pos *pos, struct winsize win,
		int len);
void			ft_cursor_right(t_pos *pos, struct winsize win, int len);
void			ft_delete_character(char *cmd, t_len_cmd *len,
		t_pos *pos);
void			ft_delete_character_2(char *cmd, t_len_cmd *len,
		t_pos *pos);
int				f_putchar(int c);
char			*find_var_env(char *name, t_struc_envp *struc_envp);
void			free_tab(char **tableau, int len_tab);
char			**ft_strsplit_space(char const *buf, char *c);
int				historique(int act, char *cmd, int len_cmd);
void			ft_key_end(char *cmd, t_pos *pos, t_len_cmd *len);
void			ft_key_home(char *cmd, t_pos *pos, t_len_cmd *len);
int				len_of_nbr_ligne(struct winsize win, int pos);
int				len_tab(char **tableau);
int				parser(char *cmd, t_struc_envp *struc_envp);
int				prepare_term(void);
int				reset_term(void);
char			*remalloc_cmd(t_len_cmd *len, char *cmd);
void			ft_signal(void);
void			ft_signal_child(void);
void			ft_write_cmd(char *buffer, char *cmd, t_pos *pos,
		t_len_cmd *len);
void			new_safe_place(int len);
void			write_new_cmd(char *cmd, t_pos *pos, int len);

#endif
