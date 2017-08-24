/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 14:47:57 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/24 14:12:45 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static void		put_buffer_to_cmd(char buffer, char *cmd, t_pos *pos, int len)
{
	int				x;
	char			tmp_cmd;
	char			tmp_buf;

	if (cmd[pos->pos] == '\0')
	{
		cmd[pos->pos] = buffer;
	}
	else
	{
		x = pos->pos;
		tmp_buf = buffer;
		while (x < (len + 2))
		{
			tmp_cmd = cmd[x];
			cmd[x] = tmp_buf;
			tmp_buf = cmd[x + 1];
			cmd[x + 1] = tmp_cmd;
			x += 2;
		}
	}
}

static void		increment_line(t_pos *pos, struct winsize win)
{
	if (pos->nbr_line > 0)
	{
		if (pos->nbr_line == 1)
		{
			if ((pos->pos - (win.ws_col - 3)) >= win.ws_col)
				pos->nbr_line++;
		}
		else
		{
			if ((pos->pos - ((win.ws_col - 3) + (win.ws_col * (pos->nbr_line
									- 1)))) >= win.ws_col)
				pos->nbr_line++;
		}
	}
	else if (pos->pos >= (win.ws_col - 3))
		pos->nbr_line++;
}

static void		place_cursor(t_pos *pos, struct winsize win)
{
	increment_line(pos, win);
	if (pos->nbr_line > 0 && pos->pos > 0)
	{
		tputs(tgoto(tgetstr("DO", NULL), 0, pos->nbr_line), 0, f_putchar);
		tputs(tgetstr("cr", NULL), 0, f_putchar);
		if (pos->nbr_line == 1)
		{
			if ((pos->pos - (win.ws_col - 3)) > 0)
				tputs(tgoto(tgetstr("RI", NULL), 0, (pos->pos - (win.ws_col
									- 3))), 0, f_putchar);
		}
		else
		{
			if ((pos->pos - ((win.ws_col - 3) + (win.ws_col *
								(pos->nbr_line - 1)))) > 0)
				tputs(tgoto(tgetstr("RI", NULL), 0, (pos->pos - ((win.ws_col
										- 3) + (win.ws_col * (pos->nbr_line
												- 1))))), 0, f_putchar);
		}
	}
	else if (pos->pos > 0)
		tputs(tgoto(tgetstr("RI", NULL), 0, pos->pos), 0, f_putchar);
}

void			write_new_cmd(char *cmd, t_pos *pos, int len)
{
	struct winsize	win;

	ioctl(0, TIOCGWINSZ, &win);
	tputs(tgetstr("rc", NULL), 0, f_putchar);
	tputs(tgetstr("cr", NULL), 0, f_putchar);
	tputs(tgoto(tgetstr("DL", NULL), win.ws_col, win.ws_row), 0, f_putchar);
	write(0, "$> ", 3);
	write(0, cmd, len);
	tputs(tgetstr("rc", NULL), 0, f_putchar);
	place_cursor(pos, win);
}

void			ft_write_cmd(char *buffer, char *cmd, t_pos *pos,
		t_len_cmd *len)
{
	int		x;

	x = 0;
	while (x < 3)
	{
		if (ft_isprint(buffer[x]) == 1)
		{
			put_buffer_to_cmd(buffer[x], cmd, pos, len->len);
			pos->pos++;
			len->len++;
			new_safe_place(len->len);
			write_new_cmd(cmd, pos, len->len);
		}
		x++;
	}
}
