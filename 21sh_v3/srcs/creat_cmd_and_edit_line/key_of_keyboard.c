/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_of_keyboard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 11:24:50 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/13 10:58:30 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static int			key_of_keyboard_2(char *buffer, t_len_cmd *len, t_pos *pos,
		t_history *history)
{
	struct winsize	win;

	ft_memset(&win, 0, sizeof(win));
	ioctl(0, TIOCGWINSZ, &win);
	if (buffer[0] == 12 && buffer[1] == 0 && buffer[2] == 0)
		clear_win(history->history[pos->history], len, pos);
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 51)
		del_multi_line(buffer, history->history[pos->history], pos, len);
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 65)
		history_down(pos, len, history, win);
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 66)
		history_up(pos, len, history, win);
	else if ((buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 70) ||
			(buffer[0] == 5 && buffer[1] == 0 && buffer[2] == 0))
		ft_key_end(history->history[pos->history], pos, len);
	else if ((buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 72) ||
			(buffer[0] == 1 && buffer[1] == 0 && buffer[2] == 0))
		ft_key_home(history->history[pos->history], pos, len);
	else if (buffer[0] == 127 && buffer[1] == 0 && buffer[2] == 0)
		ft_delete_character(history->history[pos->history], len, pos);
	else if (ft_cursor_move(buffer, pos, win, len->len) == 0)
		ft_write_cmd(buffer, history->history[pos->history], pos, len);
	return (0);
}

int					key_of_keyboard(char *buffer, t_len_cmd *len, t_pos *pos,
		t_history *history)
{
	struct winsize	win;

	ft_memset(&win, 0, sizeof(win));
	ioctl(0, TIOCGWINSZ, &win);
	if (buffer[0] == 4 && buffer[1] == 0 && buffer[2] == 0)
	{
		if (ctrl_d(pos, len, history) == 1)
			return (1);
	}
	key_of_keyboard_2(buffer, len, pos, history);
	return (0);
}
