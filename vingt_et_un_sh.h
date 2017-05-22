/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vingt_et_un_sh.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 11:57:32 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/22 13:02:07 by gsotty           ###   ########.fr       */
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

typedef struct		s_pos
{
		int			pos_x;
		int			pos_y;
}					t_pos;

int		vingt_et_un_sh(char **envp);
int		reset_term(void);
int		prepare_term(void);
int		f_putchar(int c);
char	**remalloc_env(char **envp, int after_size, int new_size);
char	**creat_env(char **envp_begin);

#endif
