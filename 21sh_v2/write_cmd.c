/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 14:47:57 by gsotty            #+#    #+#             */
/*   Updated: 2017/07/11 16:11:00 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./vingt_et_un_sh.h"

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

static void		write_new_cmd(char *cmd, t_pos *pos, int len)
{
	struct winsize	win;

	ioctl(0, TIOCGWINSZ, &win);
	tputs(tgetstr("rc", NULL), 0, f_putchar);
	tputs(tgetstr("ce", NULL), 0, f_putchar);
	tputs(tgetstr("do", NULL), 0, f_putchar);
	tputs(tgetstr("cr", NULL), 0, f_putchar);
	tputs(tgoto(tgetstr("DL", NULL), SIZE_COL_2, win.ws_row), 0, f_putchar);
	tputs(tgetstr("rc", NULL), 0, f_putchar);
	write(0, cmd, ft_strlen(cmd));
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
			write(0, buffer + x, 1);
			write_new_cmd(cmd, pos, len->len);
		}
		x++;
	}
}
