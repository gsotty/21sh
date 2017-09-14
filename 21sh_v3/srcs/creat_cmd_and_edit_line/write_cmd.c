/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 14:47:57 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/14 15:53:34 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static void		put_buffer_to_cmd(char buffer, t_lchar *cmd, t_pos *pos, int len)
{
	int				x;
	t_lchar			tmp_cmd;
	char			tmp_buf;

	if (cmd[pos->pos].c == '\0')
	{
		cmd[pos->pos].c = buffer;
	}
	else
	{
		x = pos->pos;
		tmp_buf = buffer;
		while (x < (len + 2))
		{
		
			tmp_cmd.c = cmd[x].c;
			tmp_cmd.type = cmd[x].type;
			cmd[x].c = tmp_buf;
	//		if (tmp_buf == 10)
	//			cmd[x].type = tmp_buf;
			cmd[x].type = 0;
			tmp_buf = cmd[x + 1].c;
			cmd[x + 1].c = tmp_cmd.c;
			cmd[x + 1].type = tmp_cmd.type;
			x += 2;
		}
	}
}

/*
static void		increment_line(t_pos *pos, struct winsize win)
{
	if (pos->nbr_line > 0)
	{
		if (pos->nbr_line == 1)
		{
			if ((pos->pos - (win.ws_col - _PROMPT_LEN)) >= win.ws_col)
				pos->nbr_line++;
		}
		else
		{
			if ((pos->pos - ((win.ws_col - _PROMPT_LEN) + (win.ws_col *
								(pos->nbr_line - 1)))) >= win.ws_col)
				pos->nbr_line++;
		}
	}
	else if (pos->pos >= (win.ws_col - _PROMPT_LEN))
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
			if ((pos->pos - (win.ws_col - _PROMPT_LEN)) > 0)
				tputs(tgoto(tgetstr("RI", NULL), 0, (pos->pos - (win.ws_col
									- _PROMPT_LEN))), 0, f_putchar);
		}
		else
		{
			if ((pos->pos - ((win.ws_col - _PROMPT_LEN) + (win.ws_col *
								(pos->nbr_line - 1)))) > 0)
				tputs(tgoto(tgetstr("RI", NULL), 0, (pos->pos - ((win.ws_col -
										_PROMPT_LEN) + (win.ws_col *
											(pos->nbr_line - 1))))), 0,
						f_putchar);
		}
	}
	else if (pos->pos > 0)
		tputs(tgoto(tgetstr("RI", NULL), 0, pos->pos), 0, f_putchar);
}
*/

void			write_new_cmd(t_lchar *cmd, t_pos *pos, int len)
{
	struct winsize	win;
	int				x;

	(void)pos;
	ioctl(0, TIOCGWINSZ, &win);
	tputs(tgetstr("rc", NULL), 0, f_putchar);
	tputs(tgetstr("cr", NULL), 0, f_putchar);
	tputs(tgetstr("cd", NULL), 0, f_putchar);
	write(0, _PROMPT, _PROMPT_LEN_WRITE);
	x = 0;
	while (x < len)
	{
		write(0, &cmd[x].c, 1);
		x++;
	}
	x = 0;
	while (x < (len - pos->pos))
	{
		tputs(tgetstr("le", NULL), 0, f_putchar);
		x++;
	}
//	tputs(tgetstr("rc", NULL), 0, f_putchar);
//	place_cursor(pos, win);
}

void			ft_write_cmd(char *buffer, t_lchar *cmd, t_pos *pos,
		t_len_cmd *len)
{
	int		x;

	x = 0;
	while (x < 3)
	{
		if (ft_isprint(buffer[x]) == 1 || (buffer[0] == 10 && buffer[1] == 0
					&& buffer[2] == 0 &&
					(pos->is_quote == 1 || pos->is_dquote == 1)))
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
