#include "../../include/line_edition.h"
#include "../../include/ft_termcaps.h"
#include "../../include/history.h"
#include <stdio.h>

char PC;   /* For tputs.  */
char *BC;  /* For tgoto.  */
char *UP;

int			ft_remalloc_buf(t_history *history)
{
	char		*new_buf;

	if ((new_buf = ft_memalloc(sizeof(char) * (history->len_malloc[history->pos_buf]))) == NULL)
		return (1);
	ft_memcpy(new_buf, history->buf[history->pos_buf], history->len[history->pos_buf]);
	if (history->len[history->pos_buf] != 0)
		free(history->buf[history->pos_buf]);
	history->buf[history->pos_buf] = new_buf;
	return (0);
}

int			creat_buf(t_history *history, char *buffer)
{
	int		x;
	char	tmp;
	char	tmp_buf;

	if (history->len[history->pos_buf] >= history->len_malloc[history->pos_buf])
	{
		history->len_malloc[history->pos_buf] += LEN_REMALLOC;
		if (ft_remalloc_buf(history) == 1)
			return (1);
	}
	x = history->pos[history->pos_buf];
	tmp_buf = buffer[0];
	while (x <= (history->len[history->pos_buf]))
	{
		tmp = history->buf[history->pos_buf][x];
		history->buf[history->pos_buf][x] = tmp_buf;
		tmp_buf = tmp;
		x++;
	}
	return (0);
}

static void		refresh_size_win(int type, t_history *history, t_pos *pos, int mode) // 0 = pos++, 1 = pos--
// 2 = end , 3 = start
{
	pos->co_max = tgetnum("co");
	pos->li_max = tgetnum("li");
	if (mode == 0)
	{
		pos->li_len = (history->pos[history->pos_buf] + LEN_PROMT - 1) / (pos->co_max);
		pos->co_len = (history->pos[history->pos_buf] + LEN_PROMT - 1) - ((pos->co_max) * pos->li_len);
	}
	else if (mode == 1)
	{
		pos->li_len = (history->pos[history->pos_buf] + LEN_PROMT + 1) / (pos->co_max);
		pos->co_len = (history->pos[history->pos_buf] + LEN_PROMT + 1) - ((pos->co_max) * pos->li_len);
	}
	else if (mode == 2)
	{
		pos->li_len = (history->len[history->pos_buf] + LEN_PROMT - 1) / (pos->co_max);
		pos->co_len = (history->len[history->pos_buf] + LEN_PROMT - 1) - ((pos->co_max) * pos->li_len);
	}
	else if (mode == 3)
	{
		pos->li_len = (history->pos[history->pos_buf] + LEN_PROMT) / (pos->co_max);
		pos->co_len = (history->pos[history->pos_buf] + LEN_PROMT) - ((pos->co_max) * pos->li_len);
	}
	if (mode == 3)
	{
		pos->li_pos = (0 + LEN_PROMT) / (pos->co_max);
		pos->co_pos = (0 + LEN_PROMT) - ((pos->co_max) * pos->li_pos);
	}
	else
	{
		pos->li_pos = (history->pos[history->pos_buf] + LEN_PROMT) / (pos->co_max);
		pos->co_pos = (history->pos[history->pos_buf] + LEN_PROMT) - ((pos->co_max) * pos->li_pos);
	}
}

static void		replace_cursor_start_line(t_pos *pos)
{
	int		cu_co_zero;
	int		cu_li_zero;

	(void)cu_co_zero;
	cu_co_zero = 0;
	cu_li_zero = 0;
	while (cu_li_zero < (pos->li_len))
	{
		tputs(tgetstr("up", NULL), 1, f_putchar);
		cu_li_zero++;
	}
	while (cu_co_zero <= (pos->co_len))
	{
		tputs(tgetstr("le", NULL), 1, f_putchar);
		cu_co_zero++;
	}
}

int			write_buf(t_history *history)
{
	write(0, history->buf[history->pos_buf] + history->pos[history->pos_buf], history->len[history->pos_buf] - history->pos[history->pos_buf]);
	return (0);
}

static void		replace_cursor(int type, t_history *history, t_pos *pos, int mode)
{
	int		cu_co_pos;
	int		cu_li_pos;

	cu_co_pos = 0;
	cu_li_pos = 0;
	refresh_size_win(type, history, pos, mode);
	replace_cursor_start_line(pos);
	while (cu_li_pos < (pos->li_pos))
	{
		tputs(tgetstr("do", NULL), 1, f_putchar);
		cu_li_pos++;
	}
	while (cu_co_pos < (pos->co_pos))
	{
		tputs(tgetstr("nd", NULL), 1, f_putchar);
		cu_co_pos++;
	}
}

static void		backspace_key(t_history *history)
{
	int		x;
	char	tmp;

	if ((history->pos[history->pos_buf]) > 0)
	{
		history->pos[history->pos_buf]--;
		x = history->pos[history->pos_buf];
		tputs(tgetstr("le", NULL), 1, f_putchar);
		tputs(tgetstr("dc", NULL), 1, f_putchar);
		while (x <= history->len[history->pos_buf])
		{
			tmp = history->buf[history->pos_buf][x + 1];
			history->buf[history->pos_buf][x] = tmp;
			x++;
		}
		history->len[history->pos_buf]--;
	}
}

static void		delete_key(t_history *history)
{
	int		x;
	char	tmp;

	if (history->pos[history->pos_buf] < history->len[history->pos_buf])
	{
		x = history->pos[history->pos_buf];
		tputs(tgetstr("dc", NULL), 1, f_putchar);
		while (x <= history->len[history->pos_buf])
		{
			tmp = history->buf[history->pos_buf][x + 1];
			history->buf[history->pos_buf][x] = tmp;
			x++;
		}
		history->len[history->pos_buf]--;
	}
}

/*
**
** Line edition:
**
** allor 
**
*/

int				line_edition(int type, t_history *history)
{
	char			buffer[4];
	struct winsize	win;
	t_pos			pos;
	char			*temp;

	ft_memset(&pos, 0, sizeof(t_pos));
	ioctl(0, TIOCGWINSZ, &win);
	if (init_termcaps() == 1)
		return (1);
	temp = tgetstr ("pc", NULL);
	PC = temp ? *temp : 24;
	BC = tgetstr ("le", NULL);
	UP = tgetstr ("up", NULL);
//	printf("[%i],[%i],[%i]\n", tgetnum("co"), tgetnum("it"), tgetnum("li"));
//	printf("[%d], [%d]\n", history->len_buf, history->pos_buf);
	write(0, PROMT, LEN_PROMT);
	while (1)
	{
		ft_memset(&buffer, 0, sizeof(char) * 4);
		read(0, buffer, 3);
		//printf("[%d], [%d], [%d]\n", buffer[0], buffer[1], buffer[2]);
		if (buffer[0] == 4 && buffer[1] == 0 && buffer[2] == 0)
			break ;
		if (buffer[0] == 127 && buffer[1] == 0 && buffer[2] == 0)
			backspace_key(history);
		else if (buffer[0] == 126 && buffer[1] == 0 && buffer[2] == 0)
			delete_key(history);
		else if (buffer[0] == 27 && buffer[1] == 91)
		{
			if (buffer[2] == 65 && history->pos_buf > 0) // up
			{
				replace_cursor(type, history, &pos, 3);
				history->pos_buf--;
				tputs(tgetstr("cr", NULL), 1, f_putchar);
				tputs(tgetstr("cd", NULL), 1, f_putchar);
				write(0, PROMT, LEN_PROMT);
				write(0, history->buf[history->pos_buf], history->len[history->pos_buf]);
				history->pos[history->pos_buf] = history->len[history->pos_buf];
				replace_cursor(type, history, &pos, 2);
			}
			else if (buffer[2] == 66 && history->pos_buf < history->len_buf) // down
			{
				replace_cursor(type, history, &pos, 3);
				history->pos_buf++;
				tputs(tgetstr("cr", NULL), 1, f_putchar);
				tputs(tgetstr("cd", NULL), 1, f_putchar);
				write(0, PROMT, LEN_PROMT);
				write(0, history->buf[history->pos_buf], history->len[history->pos_buf]);
				history->pos[history->pos_buf] = history->len[history->pos_buf];
				replace_cursor(type, history, &pos, 2);
			}
			else if (buffer[2] == 67 && history->pos[history->pos_buf] < history->len[history->pos_buf]) // right
			{
				history->pos[history->pos_buf]++;
				replace_cursor(type, history, &pos, 0);
			}
			else if (buffer[2] == 68 && history->pos[history->pos_buf] > 0) // left
			{
				history->pos[history->pos_buf]--;
				replace_cursor(type, history, &pos, 1);
			}
		}
		else if (buffer[0] == 10 && buffer[1] == 0 && buffer[2] == 0)
		{
			break ;
		}
		else
		{
			creat_buf(history, buffer);
			history->len[history->pos_buf]++;
			write_buf(history);
			history->pos[history->pos_buf]++;
			replace_cursor(type, history, &pos, 2);
		}
	}
	if (reset_termcaps() == 1)
		return (1);
	return (0);
}
