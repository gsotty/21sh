/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 14:47:57 by gsotty            #+#    #+#             */
/*   Updated: 2017/07/13 15:52:32 by gsotty           ###   ########.fr       */
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
	if (pos->nbr_line > 0)
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
	else
		tputs(tgoto(tgetstr("RI", NULL), 0, pos->pos), 0, f_putchar);
}

static void		write_new_cmd(char *cmd, t_pos *pos, int len)
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

static int		len_of_nbr_ligne(struct winsize win, t_pos *pos, int len)
{
	int		nbr_ligne_f;
	int		tmp_len;

	tmp_len = len;
	nbr_ligne_f = -1;
	while (tmp_len > 0)
	{
		if (nbr_ligne_f == 0)
		{
			tmp_len -= (win.ws_col - 3);
			nbr_ligne_f++;
		}
		else
		{
			tmp_len -= win.ws_col;
			nbr_ligne_f++;
		}
	}
	return (nbr_ligne_f);
}

static int		verif_creat_ligne(struct winsize win, int nbr_ligne_f,
		t_pos *pos, int len)
{
	if (nbr_ligne_f > 0)
	{
		if (nbr_ligne_f == 1)
		{
			if ((len - (win.ws_col - 3)) >= win.ws_col)
				return (1);
		}
		else
		{
			if ((len - ((win.ws_col - 3) + (win.ws_col * (nbr_ligne_f
									- 1)))) >= win.ws_col)
				return (1);
		}
	}
	else if (len >= (win.ws_col - 3))
		return (1);
	return (0);
}

static void		new_safe_place(char buffer, char *cmd, t_pos *pos, int len)
{
	struct winsize	win;
	int				creat_ligne;
	int				x;
	int				nbr_ligne_f;

	x = 0;
	ioctl(0, TIOCGWINSZ, &win);
	nbr_ligne_f = len_of_nbr_ligne(win, pos, len);
	if (verif_creat_ligne(win, nbr_ligne_f, pos, len) == 0)
	{
		tputs(tgetstr("rc", NULL), 0, f_putchar);
		while (x < (nbr_ligne_f + 1))
		{
			tputs(tgetstr("do", NULL), 0, f_putchar);
			x++;
		}
		tputs(tgoto(tgetstr("UP", NULL), 0, nbr_ligne_f + 1), 0, f_putchar);
		tputs(tgoto(tgetstr("RI", NULL), 0, 3), 0, f_putchar);
		tputs(tgetstr("sc", NULL), 0, f_putchar);
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
			new_safe_place(buffer[x], cmd, pos, len->len);
			write_new_cmd(cmd, pos, len->len);
		}
		x++;
	}
}
