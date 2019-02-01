#include "../../include/line_edition.h"
#include "../../include/ft_termcaps.h"
#include "../../include/history.h"
#include "../../include/vingt_et_un_sh.h"
#include <stdio.h>

char PC;   /* For tputs.  */
char *BC;  /* For tgoto.  */
char *UP;

int			ft_remalloc_buf(t_history *history)
{
	char		*new_buf;

	if ((new_buf = ft_memalloc(sizeof(char) *
					(history->len_malloc[history->pos_buf]))) == NULL)
		return (1);
	ft_memcpy(new_buf, history->buf[history->pos_buf],
			history->len[history->pos_buf]);
	if (history->len[history->pos_buf] != 0)
		free(history->buf[history->pos_buf]);
	if ((history->buf[history->pos_buf] = ft_memalloc(sizeof(char) *
					(history->len_malloc[history->pos_buf]))) == NULL)
		return (1);
	ft_memcpy(history->buf[history->pos_buf], new_buf,
			history->len[history->pos_buf]);
	if (history->len[history->pos_buf] != 0)
		free(new_buf);
	return (0);
}

int			creat_buf(t_history *history, char *buffer, int ret)
{
	int		new_len;
	char	*after_pos;
	int		len_after;

	new_len = history->len[history->pos_buf] + ret;
	if (new_len >= history->len_malloc[history->pos_buf])
	{
		history->len_malloc[history->pos_buf] = new_len;
		if (ft_remalloc_buf(history) == 1)
			return (1);
	}
	len_after = history->len[history->pos_buf] - history->pos[history->pos_buf];
	if (len_after > 0)
	{
		if ((after_pos = ft_memalloc(sizeof(char) * (len_after))) == NULL)
			return (1);
		ft_memcpy(after_pos, history->buf[history->pos_buf] +
				history->pos[history->pos_buf], len_after);
		ft_memcpy(history->buf[history->pos_buf] +
				history->pos[history->pos_buf], buffer, ret);
		ft_memcpy(history->buf[history->pos_buf] +
				history->pos[history->pos_buf] + ret, after_pos, len_after);
		free(after_pos);
	}
	else
	{
		ft_memcpy(history->buf[history->pos_buf] +
				history->pos[history->pos_buf], buffer, ret);
	}
	history->len[history->pos_buf] += ret;
	history->pos[history->pos_buf] += ret;
	return (0);
}

int			remalloc_struct_pos(t_pos *pos, int new_li)
{
	int		x;
	int		*new_promt_pos_cursor;
	int		*new_promt_pos_char;
	int		*new_buf_pos_pos_cursor;
	int		*new_buf_pos_pos_char;
	int		*new_buf_len_pos_cursor;
	int		*new_buf_len_pos_char;

	if ((new_promt_pos_cursor = ft_memalloc(sizeof(int) * new_li + 1)) == NULL)
		return (1);
	if ((new_promt_pos_char = ft_memalloc(sizeof(int) * new_li + 1)) == NULL)
		return (1);
	if ((new_buf_pos_pos_cursor = ft_memalloc(sizeof(int) *
					new_li + 1)) == NULL)
		return (1);
	if ((new_buf_pos_pos_char = ft_memalloc(sizeof(int) * new_li + 1)) == NULL)
		return (1);
	if ((new_buf_len_pos_cursor = ft_memalloc(sizeof(int) *
					new_li + 1)) == NULL)
		return (1);
	if ((new_buf_len_pos_char = ft_memalloc(sizeof(int) * new_li + 1)) == NULL)
		return (1);
	x = 0;
	while (x < new_li)
	{
		if (x < pos->malloc)
		{
			new_promt_pos_cursor[x] = pos->promt.pos_cursor[x];
			new_promt_pos_char[x] = pos->promt.pos_char[x];
			new_buf_pos_pos_cursor[x] = pos->buf_pos.pos_cursor[x];
			new_buf_pos_pos_char[x] = pos->buf_pos.pos_char[x];
			new_buf_len_pos_cursor[x] = pos->buf_len.pos_cursor[x];
			new_buf_len_pos_char[x] = pos->buf_len.pos_char[x];
		}
		x++;
	}
	free(pos->promt.pos_cursor);
	free(pos->promt.pos_char);
	free(pos->buf_pos.pos_cursor);
	free(pos->buf_pos.pos_char);
	free(pos->buf_len.pos_cursor);
	free(pos->buf_len.pos_char);
	if ((pos->promt.pos_cursor = ft_memalloc(sizeof(int) * new_li + 1)) == NULL)
		return (1);
	if ((pos->promt.pos_char = ft_memalloc(sizeof(int) * new_li + 1)) == NULL)
		return (1);
	if ((pos->buf_pos.pos_cursor = ft_memalloc(sizeof(int) *
					new_li + 1)) == NULL)
		return (1);
	if ((pos->buf_pos.pos_char = ft_memalloc(sizeof(int) * new_li + 1)) == NULL)
		return (1);
	if ((pos->buf_len.pos_cursor = ft_memalloc(sizeof(int) *
					new_li + 1)) == NULL)
		return (1);
	if ((pos->buf_len.pos_char = ft_memalloc(sizeof(int) * new_li + 1)) == NULL)
		return (1);
	x = 0;
	while (x < new_li)
	{
		if (x < pos->malloc)
		{
			pos->promt.pos_cursor[x] = new_promt_pos_cursor[x];
			pos->promt.pos_char[x] = new_promt_pos_char[x];
			pos->buf_pos.pos_cursor[x] = new_buf_pos_pos_cursor[x];
			pos->buf_pos.pos_char[x] = new_buf_pos_pos_char[x];
			pos->buf_len.pos_cursor[x] = new_buf_len_pos_cursor[x];
			pos->buf_len.pos_char[x] = new_buf_len_pos_char[x];
		}
		x++;
	}
	free(new_promt_pos_cursor);
	free(new_promt_pos_char);
	free(new_buf_pos_pos_cursor);
	free(new_buf_pos_pos_char);
	free(new_buf_len_pos_cursor);
	free(new_buf_len_pos_char);
	return (0);
}

int			nbr_line_for_malloc(t_pos *pos, int count_tab, char *str, int len)
{
	int		count_len;
	int		length;
	int		nbr_line;
	int		line_len;
	int		next_tab;

	length = 0;
	line_len = 0;
	nbr_line = 0;
	count_len = 0;
	while (count_len < len)
	{
		if (str[count_len] == 9)
		{
			line_len = (count_tab + length) - (pos->co_max * nbr_line);
			next_tab = ((line_len + pos->len_tab) / pos->len_tab) *
				pos->len_tab;
			if (next_tab > pos->co_max)
				next_tab = pos->co_max;
			length = (next_tab - count_tab) + (pos->co_max * nbr_line);
		}
		else
			length++;
		if ((count_tab + length) >= (pos->co_max * (nbr_line + 1)))
			nbr_line++;
		count_len++;
	}
	return (nbr_line);
}


int			length_for_malloc(t_pos *pos, int count_tab, char *str, int len)
{
	int		count_len;
	int		length;
	int		nbr_line;
	int		line_len;
	int		next_tab;

	length = 0;
	line_len = 0;
	nbr_line = 0;
	count_len = 0;
	while (count_len < len)
	{
		if (str[count_len] == 9)
		{
			line_len = (count_tab + length) - (pos->co_max * nbr_line);
			next_tab = ((line_len + pos->len_tab) / pos->len_tab) *
				pos->len_tab;
			if (next_tab > pos->co_max)
				next_tab = pos->co_max;
			length = (next_tab - count_tab) + (pos->co_max * nbr_line);
		}
		else
			length++;
		if ((count_tab + length) >= (pos->co_max * (nbr_line + 1)))
			nbr_line++;
		count_len++;
	}
	return (length);
}

int			real_length(t_pos *pos, t_real_length *struct_length,
		int count_tab, char *str, int len)
{
	int				count_len;
	int				line_len;
	int				next_tab;
	int				len_use_cursor;
	int				len_use_char;
	int				new_nbr_line;

	new_nbr_line = nbr_line_for_malloc(pos, count_tab, str, len);
	if (new_nbr_line >= pos->malloc)
	{
		if (remalloc_struct_pos(pos, pos->malloc + pos->li_max) == 1)
			return (1);
		pos->malloc += pos->li_max;
	}
	len_use_cursor = 0;
	len_use_char = 0;
	line_len = 0;
	count_len = 0;
	struct_length->len = 0;
	struct_length->nbr_line = 0;
	ft_memset(struct_length->pos_cursor, 0, pos->malloc);
	ft_memset(struct_length->pos_char, 0, pos->malloc);
	while (count_len < len)
	{
		if (str[count_len] == 9)
		{
			line_len = (count_tab + struct_length->len) - (pos->co_max *
					struct_length->nbr_line);
			next_tab = ((line_len + pos->len_tab) / pos->len_tab) *
				pos->len_tab;
			if (next_tab > pos->co_max)
				next_tab = pos->co_max;
			struct_length->len = (next_tab - count_tab) + (pos->co_max *
					struct_length->nbr_line);
		}
		else
			struct_length->len++;
		count_len++;
		struct_length->pos_cursor[struct_length->nbr_line] =
			((struct_length->len) - len_use_cursor);
		struct_length->pos_char[struct_length->nbr_line] = (count_len -
				len_use_char);
		if ((count_tab + struct_length->len) >= (pos->co_max *
					(struct_length->nbr_line + 1)))
		{
			len_use_char = count_len;
			len_use_cursor = struct_length->len;
			struct_length->nbr_line++;
			struct_length->pos_cursor[struct_length->nbr_line] = 0;
			struct_length->pos_char[struct_length->nbr_line] = 0;
		}
	}
	int x;
	x = struct_length->nbr_line + 1;
	while (x < pos->malloc)
	{
		struct_length->pos_cursor[x] = 0;
		struct_length->pos_char[x] = 0;
		x++;
	}
	x = 0;
	while (x < pos->malloc)
	{
		fprintf(stderr, "pos_char = [%d], pos_cursor = [%d]\n", struct_length->pos_char[x], struct_length->pos_cursor[x]);
		x++;
	}
	return (0);
}

int				nbr_line_total(t_pos *pos)
{
	int	nbr_line_pos;
	int	nbr_line_len;

	nbr_line_pos = 0;
	fprintf(stderr, "	li_max = [%d], co_max = [%d]\n", pos->li_max, pos->co_max);
	while ((pos->promt.pos_cursor[nbr_line_pos] +
				pos->buf_pos.pos_cursor[nbr_line_pos]) >= pos->co_max
			&& nbr_line_pos < pos->malloc)
		nbr_line_pos++;
	pos->nbr_line_pos = nbr_line_pos;
	nbr_line_len = 0;
	while ((pos->promt.pos_cursor[nbr_line_len] +
			pos->buf_len.pos_cursor[nbr_line_len]) >= pos->co_max
			&& nbr_line_len < pos->malloc)
		nbr_line_len++;
	pos->nbr_line_len = nbr_line_len;
	return (0);
}

int			refresh_size_win(int type, t_history *history, t_pos *pos)
{
	pos->co_max = tgetnum("co") - 1;
	pos->li_max = tgetnum("li");
	pos->len_tab = tgetnum ("it");
	fprintf(stderr, "	promt\n");
	real_length(pos, &pos->promt, 0, PROMT, LEN_PROMT);
	fprintf(stderr, "	buf_pos\n");
	real_length(pos, &pos->buf_pos, pos->promt.len,
			history->buf[history->pos_buf], history->pos[history->pos_buf]);
	fprintf(stderr, "	buf_len\n");
	real_length(pos, &pos->buf_len, pos->promt.len,
			history->buf[history->pos_buf], history->len[history->pos_buf]);
	nbr_line_total(pos);
	fprintf(stderr, "		pos->nbr_line_pos = [%d]\n", pos->nbr_line_pos);
	fprintf(stderr, "		pos->nbr_line_len = [%d]\n", pos->nbr_line_len);
	return (0);
}

void		replace_cursor(int type, t_history *history, t_pos *pos,
		int mode)
{
	int		count_line;
	int		count_pos;

	refresh_size_win(type, history, pos);
	if (mode == 0) // go to the new pos with pos at the start
	{
		count_line = 0;
		while (count_line < pos->nbr_line_pos)
		{
			tputs(tgetstr("do", NULL), 0, f_putchar);
			count_line++;
		}
		count_pos = 0;
		while (count_pos < (pos->buf_pos.pos_cursor[count_line] +
					pos->promt.pos_cursor[count_line]))
		{
			tputs(tgetstr("nd", NULL), 0, f_putchar);
			count_pos++;
		}
	}
	else if (mode == 1) // go to the start with pos at the last pos know
	{
		tputs(tgetstr("cr", NULL), 0, f_putchar);
		count_line = 0;
		while (count_line < pos->nbr_line_pos)
		{
			if (count_line > (pos->nbr_line_pos - pos->li_max))
				tputs(tgetstr("sr", NULL), 0, f_putchar);
			else
				tputs(tgetstr("up", NULL), 0, f_putchar);
			count_line++;
		}
	}
	else if (mode == 2) // go to the start with pos at the end
	{
		tputs(tgetstr("cr", NULL), 0, f_putchar);
		count_line = 0;
		while (count_line < pos->nbr_line_len)
		{
			if (count_line > (pos->nbr_line_len - pos->li_max))
				tputs(tgetstr("sr", NULL), 0, f_putchar);
			else
				tputs(tgetstr("up", NULL), 0, f_putchar);
			count_line++;
		}
	}
	else if (mode == 3) // go to the new_pos with pos at the end
	{
		count_line = pos->nbr_line_pos;
		while (count_line < pos->nbr_line_len)
		{
			if (count_line > (pos->nbr_line_len - pos->li_max))
				tputs(tgetstr("sr", NULL), 0, f_putchar);
			else
				tputs(tgetstr("up", NULL), 0, f_putchar);
			count_line++;
		}
		tputs(tgetstr("cr", NULL), 0, f_putchar);
		count_pos = 0;
		while (count_pos < (pos->buf_pos.pos_cursor[pos->nbr_line_pos] +
					pos->promt.pos_cursor[pos->nbr_line_pos]))
		{
			tputs(tgetstr("nd", NULL), 0, f_putchar);
			count_pos++;
		}
	}
	else if (mode == 4) // go to the end with pos at the last pos know
	{
		count_line = pos->nbr_line_pos;
		while (count_line < pos->nbr_line_len)
		{
			tputs(tgetstr("do", NULL), 0, f_putchar);
			count_line++;
		}
		tputs(tgetstr("cr", NULL), 0, f_putchar);
		count_pos = 0;
		while (count_pos < (pos->buf_pos.pos_cursor[pos->nbr_line_len] +
					pos->promt.pos_cursor[pos->nbr_line_len]))
		{
			tputs(tgetstr("nd", NULL), 0, f_putchar);
			count_pos++;
		}
	}
}

void		backspace_key(t_history *history)
{
	int		x;
	char	tmp;

	if ((history->pos[history->pos_buf]) > 0)
	{
		history->pos[history->pos_buf]--;
		x = history->pos[history->pos_buf];
		while (x <= history->len[history->pos_buf])
		{
			tmp = history->buf[history->pos_buf][x + 1];
			history->buf[history->pos_buf][x] = tmp;
			x++;
		}
		history->len[history->pos_buf]--;
	}
}

void		delete_key(t_history *history)
{
	int		x;
	char	tmp;

	if (history->pos[history->pos_buf] < history->len[history->pos_buf])
	{
		x = history->pos[history->pos_buf];
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
 ** 0 = normal exit
 ** 1 = normal error
 ** 2 = exit for quit the term (like ctrl-D)
 ** 3 = exit for clean the buff and add a new ligne (ctrl-C)
 **
 */

/*

   save curent possition = `sc' "<ESC>7" same
   return to the position save = `rc' "<ESC>8" same
   move the cursor to the up = `up' "<ESC>[{count}A"		^ "<ESC>[A"
   move the cursor to the down = `do' "<ESC>[{count}B"		v "\n"
   move the cursor to the right = `nd' "<ESC>[{count}C"	> "<ESC>[C"
   move the cursor to the left = `le' "<ESC>[{count}D"		< "\b"
   move the cursor to the start of the ligne = `cr' "\r"
   clean the ligne with the cursor and all the ligne below = `cd' "<ESC>[J"
   delete the char at the position of the cursor = `dc' "<ESC>[P"

*/

int				creat_struct_pos(int type, t_pos *pos)
{
	(void)type;
	pos->co_max = tgetnum("co") - 1;
	pos->li_max = tgetnum("li");
	pos->len_tab = tgetnum ("it");

	pos->malloc = 1;

	pos->promt.len = 0;
	pos->promt.nbr_line = 0;
	if ((pos->promt.pos_cursor = ft_memalloc(sizeof(int) *
					pos->malloc)) == NULL)
		return (1);
	if ((pos->promt.pos_char = ft_memalloc(sizeof(int) *
					pos->malloc)) == NULL)
		return (1);

	pos->buf_pos.len = 0;
	pos->buf_pos.nbr_line = 0;
	if ((pos->buf_pos.pos_cursor = ft_memalloc(sizeof(int) *
					pos->malloc)) == NULL)
		return (1);
	if ((pos->buf_pos.pos_char = ft_memalloc(sizeof(int) *
					pos->malloc)) == NULL)
		return (1);

	pos->buf_len.len = 0;
	pos->buf_len.nbr_line = 0;
	if ((pos->buf_len.pos_cursor = ft_memalloc(sizeof(int) *
					pos->malloc)) == NULL)
		return (1);
	if ((pos->buf_len.pos_char = ft_memalloc(sizeof(int) *
					pos->malloc)) == NULL)
		return (1);
	return (0);
}

int		free_pos(t_pos *pos)
{
	free(pos->promt.pos_cursor);
	free(pos->promt.pos_char);
	free(pos->buf_pos.pos_cursor);
	free(pos->buf_pos.pos_char);
	free(pos->buf_len.pos_cursor);
	free(pos->buf_len.pos_char);
	return (0);
}

int				print_the_buf(int type, t_history *history, t_pos *pos)
{
	int		x;
	int		len_use_promt;
	int		len_use_buf;

	x = 0;
	len_use_buf = 0;
	len_use_promt = 0;
	refresh_size_win(type, history, pos);
	while (x <= pos->nbr_line_len)
	{
		write(STDOUT_FILENO, PROMT + len_use_promt, pos->promt.pos_char[x]);
		write(STDOUT_FILENO, history->buf[history->pos_buf] + len_use_buf,
				pos->buf_len.pos_char[x]);
		len_use_promt += pos->promt.pos_char[x];
		len_use_buf += pos->buf_len.pos_char[x];
		if (x < pos->nbr_line_len)
			tputs(tgetstr("do", NULL), 0, f_putchar);
		x++;
	}
	replace_cursor(type, history, pos, 3);
//	replace_cursor(type, history, pos, 2);
//	replace_cursor(type, history, pos, 0);
	return (0);
}

int				line_edition(int type, t_history *history)
{
	char			buffer[4095];
	struct winsize	win;
	t_pos			pos;
	char			*temp;
	int				ret;

#ifdef Unix
	/* Here we assume that an explicit term_buffer
	   was provided to tgetent.  */
	char *buffer = (char *) malloc (strlen (term_buffer));
#define BUFFADDR &buffer
#else
#define BUFFADDR 0
#endif

	(void)history;
	ft_memset(&pos, 0, sizeof(t_pos));
	ioctl(0, TIOCGWINSZ, &win);
	if (init_termcaps() == 1)
		return (1);
	temp = tgetstr ("pc", BUFFADDR);
	PC = temp ? *temp : 0;
	BC = tgetstr ("le", BUFFADDR);
	UP = tgetstr ("up", BUFFADDR);
	if (creat_struct_pos(type, &pos) == 1)
		return (1);
	write(1, PROMT, LEN_PROMT);
	while (1)
	{
		ft_memset(&buffer, 0, sizeof(char) * 4);
		ret = read(0, buffer, 4095);
/*		int		print = 0;
		printf("ret = [%d]\n", ret);
		while (print < ret)
		{
			printf("[%d]", buffer[print]);
			print++;
		}
		printf("\n");*/
//		write(1, buffer, ret);
		if (g_sig == SIGINT)
		{
			g_sig = 0;
			replace_cursor(type, history, &pos, 2);
			history->pos[history->pos_buf] = history->len[history->pos_buf];
			replace_cursor(type, history, &pos, 0);
			free_pos(&pos);
			if (reset_termcaps() == 1)
				return (1);
			return (3);
		}
		if (buffer[0] == 4 && ret == 1 &&
				history->len[history->pos_buf] == 0)
		{
			replace_cursor(type, history, &pos, 2);
			history->pos[history->pos_buf] = history->len[history->pos_buf];
			replace_cursor(type, history, &pos, 0);
			free_pos(&pos);
			if (reset_termcaps() == 1)
				return (1);
			return (2);
		}
		else if (buffer[0] == 4 && ret == 1)
		{
			replace_cursor(type, history, &pos, 1);
			tputs(tgetstr("cd", NULL), 0, f_putchar);
			delete_key(history);
			print_the_buf(type, history, &pos);
		}
		else if (buffer[0] == 127 && ret == 1)
		{
			replace_cursor(type, history, &pos, 1);
			tputs(tgetstr("cd", NULL), 0, f_putchar);
			backspace_key(history);
			print_the_buf(type, history, &pos);
		}
		else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 51)
		{
			replace_cursor(type, history, &pos, 1);
			tputs(tgetstr("cd", NULL), 0, f_putchar);
			delete_key(history);
			print_the_buf(type, history, &pos);
		}
		else if (buffer[0] == 27 && buffer[1] == 91)
		{
			if (buffer[2] == 65 && history->pos_buf > 0) // up
			{
				replace_cursor(type, history, &pos, 1);
				tputs(tgetstr("cd", NULL), 0, f_putchar);
				history->pos_buf--;
				history->pos[history->pos_buf] = history->len[history->pos_buf];
				print_the_buf(type, history, &pos);
			}
			else if (buffer[2] == 66 && history->pos_buf <
					history->len_buf) // down
			{
				replace_cursor(type, history, &pos, 1);
				tputs(tgetstr("cd", NULL), 0, f_putchar);
				history->pos_buf++;
				history->pos[history->pos_buf] = history->len[history->pos_buf];
				print_the_buf(type, history, &pos);
			}
			else if (buffer[2] == 67 && pos.buf_pos.len <
					pos.buf_len.len) // right
			{
				replace_cursor(type, history, &pos, 1);
				tputs(tgetstr("cd", NULL), 0, f_putchar);
				history->pos[history->pos_buf]++;
				print_the_buf(type, history, &pos);
			}
			else if (buffer[2] == 68 && pos.buf_pos.len > 0) // left
			{
				replace_cursor(type, history, &pos, 1);
				tputs(tgetstr("cd", NULL), 0, f_putchar);
				history->pos[history->pos_buf]--;
				print_the_buf(type, history, &pos);
			}
			else if (buffer[2] == 72) // home
			{
				replace_cursor(type, history, &pos, 1);
			}
		}
		else if (buffer[0] == 10 && buffer[1] == 0 && buffer[2] == 0)
		{
			break ;
		}
		else
		{
			replace_cursor(type, history, &pos, 1);
			tputs(tgetstr("cd", NULL), 0, f_putchar);
			creat_buf(history, buffer, ret);
			print_the_buf(type, history, &pos);
		}
	}
	replace_cursor(type, history, &pos, 2);
	history->pos[history->pos_buf] = history->len[history->pos_buf];
	replace_cursor(type, history, &pos, 0);
	free_pos(&pos);
	if (reset_termcaps() == 1)
		return (1);
	return (0);
}
