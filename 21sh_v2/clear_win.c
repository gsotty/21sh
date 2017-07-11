/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_win.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 16:42:08 by gsotty            #+#    #+#             */
/*   Updated: 2017/07/11 17:08:33 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./vingt_et_un_sh.h"

void	clear_win(char *cmd, t_len_cmd *len, t_pos *pos, struct winsize win)
{
	tputs(tgetstr("cl", NULL), 0, f_putchar);
	write(0, "$> ", 3);
	tputs(tgetstr("sc", NULL), 0, f_putchar);
	write(0, cmd, len->len);
	tputs(tgetstr("rc", NULL), 0, f_putchar);
	if ((pos->pos - (SIZE_COL_2 * pos->nbr_line)) >= SIZE_COL_2)
	{
		pos->nbr_line++;
		tputs(tgetstr("cr", NULL), 0, f_putchar);
	}
	else
	{
		tputs(tgoto(tgetstr("RI", NULL), 0, (pos->pos -
						(SIZE_COL_2 * pos->nbr_line))), 0, f_putchar);
	}
	if (pos->nbr_line > 0)
	{
		tputs(tgoto(tgetstr("DO", NULL), 0, pos->nbr_line), 0, f_putchar);
	}
}
