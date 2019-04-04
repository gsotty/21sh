/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcaps.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 16:30:09 by gsotty            #+#    #+#             */
/*   Updated: 2019/04/04 16:30:56 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TERMCAPS_H
# define FT_TERMCAPS_H

# include "../lib/libft/libft.h"
# include "./line_edition.h"
# include "./history.h"
# include <ncurses.h>
# include <term.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct		s_sequence
{
	char			*reset;
	char			*start_buf;
	char			*buffer;
	char			*start;
	char			*end;
	char			*left_cursor;
	char			*right_cursor;
	char			*up_scroll;
	char			*down_scroll;
	char			*go_start_line;
	char			*clear_rest_screen;
}					t_sequence;

typedef struct		s_key
{
	char			*str;
}					t_key;

typedef struct		s_which_key
{
	char			*key;
	int				(*f)(t_sequence *sequence, t_pos *pos, t_promt promt,
			t_history *history);
}					t_which_key;

int					f_putchar(int c);
int					ft_init_termcaps(t_key *key, t_sequence *sequence);
int					ft_reset_termcaps(t_sequence *sequence);

#endif
