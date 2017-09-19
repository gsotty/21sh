/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 13:56:27 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/19 14:52:08 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static void		one_ligne(t_pos *pos, struct winsize win)
{
	if (((pos->pos - 1) - (win.ws_col - _PROMPT_LEN)) < 0)
	{
		tputs(tgetstr("up", NULL), 0, f_putchar);
		tputs(tgoto(tgetstr("RI", NULL), 0, win.ws_col), 0, f_putchar);
		pos->nbr_line--;
		pos->pos--;
	}
	else
	{
		tputs(tgetstr("le", NULL), 0, f_putchar);
		pos->pos--;
	}
}

static void		multi_ligne(t_pos *pos, struct winsize win)
{
	if (((pos->pos - 1) - ((win.ws_col - _PROMPT_LEN) + (win.ws_col *
						(pos->nbr_line - 1)))) < 0)
	{
		tputs(tgetstr("up", NULL), 0, f_putchar);
		tputs(tgoto(tgetstr("RI", NULL), 0, win.ws_col), 0, f_putchar);
		pos->nbr_line--;
		pos->pos--;
	}
	else
	{
		tputs(tgetstr("le", NULL), 0, f_putchar);
		pos->pos--;
	}
}

static void		cursor_left_multiligne(t_pos *pos, struct winsize win)
{
	if (pos->nbr_line == 1)
	{
		one_ligne(pos, win);
	}
	else
	{
		multi_ligne(pos, win);
	}
}

void			ft_cursor_left(t_pos *pos, struct winsize win)
{
	if (pos->nbr_line > 0)
	{
		cursor_left_multiligne(pos, win);
	}
	else if ((pos->pos - 1) >= 0)
	{
		tputs(tgetstr("le", NULL), 0, f_putchar);
		pos->pos--;
	}
}
