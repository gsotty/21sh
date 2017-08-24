/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 14:41:36 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/24 15:43:24 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int		ft_cursor_move(char *buffer, t_pos *pos, struct winsize win, int len)
{
	if ((buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 68) ||
			(buffer[0] == 2 && buffer[1] == 0 && buffer[3] == 0))
	{
		ft_cursor_left(pos, win);
		return (1);
	}
	else if ((buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 67) ||
			(buffer[0] == 6 && buffer[1] == 0 && buffer[3] == 0))
	{
		ft_cursor_right(pos, win, len);
		return (1);
	}
	return (0);
}
