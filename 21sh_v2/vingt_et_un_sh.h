/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vingt_et_un_sh.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 11:57:32 by gsotty            #+#    #+#             */
/*   Updated: 2017/07/20 15:32:16 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VINGT_ET_UN_SH_H
# define VINGT_ET_UN_SH_H

# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>
# include <term.h>
# include <stdlib.h>
# include <curses.h>
# include <sys/ioctl.h>

# define LEN_REMALLOC 10
# define SIZE_COL ((pos.nbr_line == 0) ? (win.ws_col - 3) : win.ws_col)
# define SIZE_COL_2 ((pos->nbr_line == 0) ? (win.ws_col - 3) : win.ws_col)

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

char			**creat_envp(char **envp, int len_envp);
int				len_tab(char **tableau);
void			free_tab(char **tableau, int len_tab);
int				f_putchar(int c);
int				prepare_term(void);
int				reset_term(void);
void			ft_cursor_left(t_pos *pos, struct winsize win);
void			ft_cursor_right(t_pos *pos, struct winsize win, int len);
int				ft_cursor_move(char *buffer, t_pos *pos,
		struct winsize win, int len);
void			ft_write_cmd(char *buffer, char *cmd, t_pos *pos,
		t_len_cmd *len);
char			*remalloc_cmd(t_len_cmd *len, char *cmd);
void			clear_win(char *cmd, t_len_cmd *len, t_pos *pos,
		struct winsize win);
void			new_safe_place(int len);
void			ft_delete_character(char *cmd, t_len_cmd *len,
		t_pos *pos);
void			write_new_cmd(char *cmd, t_pos *pos, int len);

#endif
