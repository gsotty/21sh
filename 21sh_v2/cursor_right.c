/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_right.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 14:38:20 by gsotty            #+#    #+#             */
/*   Updated: 2017/07/11 14:40:56 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./vingt_et_un_sh.h"

void	ft_cursor_right(t_pos *pos, struct winsize win, int len)
{
	if (((pos->pos + 1) - (SIZE_COL_2 * pos->nbr_line))
			<= (len - (SIZE_COL_2 * pos->nbr_line)))
	{
		tputs(tgetstr("nd", NULL), 0, f_putchar);
		pos->pos++;
	}
	if (((pos->pos + 1) - (SIZE_COL_2 * pos->nbr_line))
			>= SIZE_COL_2)
	{
		tputs(tgetstr("do", NULL), 0, f_putchar);
		pos->nbr_line++;
		pos->pos++;
	}
}
