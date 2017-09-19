/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_right.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 14:38:20 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/19 14:09:57 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static void		one_ligne(t_pos *pos, struct winsize win)
{
	if (((pos->pos + 1) - (win.ws_col - _PROMPT_LEN)) >= win.ws_col)
	{
		tputs(tgetstr("do", NULL), 0, f_putchar);
		pos->nbr_line++;
		pos->pos++;
	}
	else if (((pos->pos + 1) - (win.ws_col - _PROMPT_LEN)) <= (pos->len -
				(win.ws_col - _PROMPT_LEN)))
	{
		tputs(tgetstr("nd", NULL), 0, f_putchar);
		pos->pos++;
	}
}

static void		multi_ligne(t_pos *pos, struct winsize win)
{
	if (((pos->pos + 1) - ((win.ws_col - _PROMPT_LEN) + (win.ws_col *
						(pos->nbr_line - 1)))) >= win.ws_col)
	{
		tputs(tgetstr("do", NULL), 0, f_putchar);
		pos->nbr_line++;
		pos->pos++;
	}
	else if (((pos->pos + 1) - ((win.ws_col - _PROMPT_LEN) + (win.ws_col *
						(pos->nbr_line - 1)))) <= (pos->len - ((win.ws_col -
							_PROMPT_LEN) + (win.ws_col * (pos->nbr_line - 1)))))
	{
		tputs(tgetstr("nd", NULL), 0, f_putchar);
		pos->pos++;
	}
}

static void		cursor_right_multiligne(t_pos *pos, struct winsize win)
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

void			ft_cursor_right(t_pos *pos, struct winsize win)
{
	if (pos->nbr_line > 0)
	{
		cursor_right_multiligne(pos, win);
	}
	else
	{
		if ((pos->pos + 1) >= (win.ws_col - _PROMPT_LEN))
		{
			tputs(tgetstr("do", NULL), 0, f_putchar);
			pos->nbr_line++;
			pos->pos++;
		}
		else if ((pos->pos + 1) <= pos->len)
		{
			tputs(tgetstr("nd", NULL), 0, f_putchar);
			pos->pos++;
		}
	}
}
