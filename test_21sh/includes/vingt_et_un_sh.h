/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vingt_et_un_sh.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 11:57:32 by gsotty            #+#    #+#             */
/*   Updated: 2017/06/02 11:38:26 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VINGT_ET_UN_SH_H
# define VINGT_ET_UN_SH_H

# include "./libft/libft.h"
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

sig_atomic_t		g_sig;

typedef struct		s_pos
{
	int				pos_x;
	int				pos_y;
}					t_pos;

typedef struct		s_split
{
	int				j;
	int				x;
}					t_split;

void				ft_env(char **cmd);
void				free_tab(char **tab_1);
int					ft_echo(char **argv);
void				ft_setenv(char **cmd);
void				ft_unsetenv(char **cmd);
void				cd(char **argv);
void				exe_fork(int argc, char **argv);

void				parser(char *buf, char **envp);
int					vingt_et_un_sh(char **envp);
int					reset_term(void);
int					prepare_term(void);
int					f_putchar(int c);
char				**remalloc_env(char **envp, int after_size, int new_size);
char				**creat_env(char **envp_begin);
char				**ft_strsplit_space(char const *buf, char *c);

#endif
