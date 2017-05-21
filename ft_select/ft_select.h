/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 08:55:15 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/20 12:21:23 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "./libft/libft.h"
# include <unistd.h>
# include <term.h>
# include <stdlib.h>
# include <curses.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct		s_buf
{
	int		pos;
	int		argc;
	int		col;
	int		lig;
	int		max_len;
	int		max_lig;
	int		max_col;
	int		*nbr;
	char	**tab_arg;
}					t_buf;

sig_atomic_t		g_sig;

void				read_ft_select(t_buf *buf);
void				signal_int(int x, siginfo_t *siginfo, void *context);
int					reset_term(void);
int					prepare_term(void);
void				signal_tstp(int x, siginfo_t *siginfo, void *context);
void				signal_cont(int x, siginfo_t *siginfo, void *context);
int					f_putchar(int c);
void				delete_bar(t_buf *buf);
void				return_bar(t_buf *buf);
void				space_bar(t_buf *buf);
void				fleche_directionnelle(char *buffer, t_buf *buf);
int					ft_print_argv(t_buf *buf);
void				print_sur(t_buf *buf, int pos, int len);
void				print_sou(t_buf *buf, int pos, int len);
void				print_sur_et_sou(t_buf *buf, int pos, int len);
void				ft_exit(int x, t_buf *buf, char *err);
void				free_buf(t_buf *buf);
void				all_select(t_buf *buf);

#endif
