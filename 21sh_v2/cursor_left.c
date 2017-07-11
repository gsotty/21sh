/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 13:56:27 by gsotty            #+#    #+#             */
/*   Updated: 2017/07/11 14:37:57 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./vingt_et_un_sh.h"

void	ft_cursor_left(t_pos *pos, struct winsize win)
{
	if (((pos->pos - 1) - (SIZE_COL_2 * pos->nbr_line)) >= 0)
	{
		tputs(tgetstr("le", NULL), 0, f_putchar);
		pos->pos--;
	}
	else if (((pos->pos - 1) - (SIZE_COL_2 * pos->nbr_line)) <= 0
			&& pos->pos > 0 && pos->nbr_line > 0)
	{
		tputs(tgetstr("up", NULL), 0, f_putchar);
		tputs(tgoto(tgetstr("RI", NULL), 0,
					SIZE_COL_2), 0, f_putchar);
		pos->nbr_line--;
		pos->pos--;
	}
}
