#include "../../include/line_edition.h"
#include "../../include/ft_termcaps.h"
#include "../../include/history.h"
#include "../../include/vingt_et_un_sh.h"
#include "../../include/parser.h"
#include <stdio.h>

int			ft_freelchar(t_lchar *buf)
{
	free(buf->c);
	free(buf->type);
	return (0);
}

int			ft_remalloc_buf(t_history *history, int ret)
{
	t_lchar		new_buf;

	ft_lchardup(&new_buf, history->buf[history->pos_buf], 0);
	ft_freelchar(history->buf[history->pos_buf]);
	ft_lchardup(history->buf[history->pos_buf], &new_buf, ret);
	ft_freelchar(&new_buf);
	return (0);
}

int			creat_buf(t_history *history, char *buffer, int ret)
{
	int		tmp_len;
	char	*after_pos;
	int		len_after;

	tmp_len = history->buf[history->pos_buf]->len;
	if (ft_remalloc_buf(history, ret) == 1)
		return (1);
	len_after = tmp_len - history->pos[history->pos_buf];
	if (len_after > 0)
	{
		if ((after_pos = ft_memalloc(sizeof(char) * (len_after + 1))) == NULL)
			return (1);
		ft_memcpy(after_pos, history->buf[history->pos_buf]->c +
				history->pos[history->pos_buf], len_after);
		ft_memcpy(history->buf[history->pos_buf]->c +
				history->pos[history->pos_buf], buffer, ret);
		ft_memcpy(history->buf[history->pos_buf]->c +
				(history->pos[history->pos_buf] + ret), after_pos, len_after);
		ft_addtype(history->buf[history->pos_buf],
				history->pos[history->pos_buf],
				history->pos[history->pos_buf] + ret + len_after);
		free(after_pos);
	}
	else
	{
		ft_memcpy(history->buf[history->pos_buf]->c +
				history->pos[history->pos_buf], buffer, ret);
		ft_addtype(history->buf[history->pos_buf],
				history->pos[history->pos_buf],
				history->pos[history->pos_buf] + ret);
	}
	history->pos[history->pos_buf] += ret;
	return (0);
}

void		ft_real_len_char_before(int len_promt, char *str,
		t_calcul_len *line)
{
	if (str[line->count - len_promt] == 9)
	{
		line->count++;
		line->len = (line->real - line->start_cursor);
		line->rest = line->len_tab - (line->len - ((line->len / line->len_tab) *
					line->len_tab));
		if ((line->len + line->rest) >= line->co_max)
			line->real += line->len_tab - ((line->len + line->rest) -
					line->co_max);
		else
			line->real += line->rest;
	}
	else if (str[line->count - len_promt] == 10)
	{
		line->count++;
		line->start_char = line->count;
		line->start_cursor = line->real;
		line->nbr_char++;
		line->nbr_cursor++;
	}
	else
	{
		line->count++;
		line->real++;
	}
}

void		ft_real_len_char_after(t_calcul_len *line)
{
	line->len = (line->real - line->start_cursor);
	if (line->len >= line->co_max)
	{
		line->start_char = line->count;
		line->start_cursor = line->real;
		line->nbr_char++;
		line->nbr_cursor++;
	}
}

void		nbr_line_for_malloc(t_calcul_len *line, t_promt promt,
		int pos_len, t_lchar *buf)
{
	line->start_char = 0;
	line->start_cursor = 0;
	while (line->count < promt.len + buf->len)
	{
		if (line->count < promt.len)
		{
			ft_real_len_char_before(0, promt.str, line);
			ft_real_len_char_after(line);
		}
		else if (line->count - promt.len < pos_len)
		{
			ft_real_len_char_before(promt.len, buf->c, line);
			ft_real_len_char_after(line);
		}
		else if (line->count - promt.len < buf->len)
		{
			ft_real_len_char_before(promt.len, buf->c, line);
			ft_real_len_char_after(line);
		}
	}
}

void		ft_add_reallength_before(t_length *pos, int promt_char,
		int promt_cursor, char *str, t_calcul_len *line)
{
	(void)pos;
	(void)promt_char;
	(void)promt_cursor;
	if (str[line->count - line->len_promt] == 9)
	{
		line->count++;
		line->len = (line->real - line->start_cursor);
		pos->pos_char[line->nbr_cursor] = (line->count - line->start_char) - promt_char;
		pos->pos_cursor[line->nbr_cursor] = (line->len - promt_cursor);
		line->rest = line->len_tab - (line->len - ((line->len / line->len_tab) *
					line->len_tab));
		if ((line->len + line->rest) >= line->co_max)
		{
			line->real += line->len_tab - ((line->len + line->rest) -
					line->co_max);
		}
		else
		{
			line->real += line->rest;
		}
	}
	else if (str[line->count - line->len_promt] == 10)
	{
		line->start_char = line->count;
		line->start_cursor = line->real;
		line->nbr_char++;
		line->nbr_cursor++;
		line->count++;
	}
	else
	{
		line->real++;
		line->count++;
	}
}

void		ft_add_reallength_after(t_length *pos, int promt_char,
		int promt_cursor, t_calcul_len *line)
{
	(void)promt_char;
	(void)promt_cursor;
	line->len = (line->real - line->start_cursor);
	pos->pos_char[line->nbr_cursor] = (line->count - line->start_char) - promt_char;
	pos->pos_cursor[line->nbr_cursor] = (line->len - promt_cursor);
	if (line->len >= line->co_max)
	{
		line->start_char = line->count;
		line->start_cursor = line->real;
		line->nbr_char++;
		line->nbr_cursor++;
	}
}

void		ft_addvalue_lenbuf(t_pos *pos, t_calcul_len *line,
		t_promt promt, int pos_len, t_lchar *buf)
{
	line->real = 0;
	line->count = 0;
	line->start_char = 0;
	line->start_cursor = 0;
	while (line->count < promt.len + buf->len)
	{
		if (line->count < promt.len)
		{
			ft_add_reallength_before(pos->promt, 0, 0, promt.str, line);
			ft_add_reallength_after(pos->promt, 0, 0, line);
			line->len_promt = line->count;
			line->real_promt = line->real;
			pos->nbr_pos = line->nbr_cursor;
			pos->char_pos = pos->promt->pos_char[line->nbr_cursor] +
				pos->buf->pos_char[line->nbr_cursor];
			pos->cursor_pos = pos->promt->pos_cursor[line->nbr_cursor] +
				pos->buf->pos_cursor[line->nbr_cursor];
		}
		else if (line->count - promt.len < pos_len)
		{
			ft_add_reallength_before(pos->buf,
					pos->promt->pos_char[line->nbr_cursor],
					pos->promt->pos_cursor[line->nbr_cursor],
					buf->c, line);
			ft_add_reallength_after(pos->buf,
					pos->promt->pos_char[line->nbr_cursor],
					pos->promt->pos_cursor[line->nbr_cursor],
					line);
			pos->nbr_pos = line->nbr_cursor;
			pos->char_pos = pos->promt->pos_char[line->nbr_cursor] +
				pos->buf->pos_char[line->nbr_cursor];
			pos->cursor_pos = pos->promt->pos_cursor[line->nbr_cursor] +
				pos->buf->pos_cursor[line->nbr_cursor];
		}
		else if (line->count - promt.len < buf->len)
		{
			ft_add_reallength_before(pos->buf,
					pos->promt->pos_char[line->nbr_cursor],
					pos->promt->pos_cursor[line->nbr_cursor],
					buf->c, line);
			ft_add_reallength_after(pos->buf,
					pos->promt->pos_char[line->nbr_cursor],
					pos->promt->pos_cursor[line->nbr_cursor],
					line);
		}
		else
		{
			line->count++;
			line->real++;
			line->len = (line->real - line->start_cursor);
			pos->buf->pos_char[line->nbr_cursor] = (line->count - line->start_char) -
				pos->promt->pos_char[line->nbr_cursor];
			pos->buf->pos_cursor[line->nbr_cursor] = (line->len -
					pos->promt->pos_cursor[line->nbr_cursor]);
		}
	}
}

int			ft_malloc_real_length(int len, t_length *struc)
{
	if (struc->pos_char != NULL)
		free(struc->pos_char);
	if ((struc->pos_char = ft_memalloc(sizeof(t_length) * (len + 1))) == NULL)
		return (1);
	if (struc->pos_cursor != NULL)
		free(struc->pos_cursor);
	if ((struc->pos_cursor = ft_memalloc(sizeof(t_length) * (len + 1))) == NULL)
		return (1);
	return (0);
}

int			real_length(t_pos *pos, t_promt promt, int pos_len, t_lchar *buf)
{
	t_calcul_len	line;

	if ((pos->buf = ft_memalloc(sizeof(t_length) + 1)) == NULL)
		return (1);
	if ((pos->promt = ft_memalloc(sizeof(t_length) + 1)) == NULL)
		return (1);
	ft_memset(&line, 0, sizeof(t_calcul_len));
	line.co_max = tgetnum("co");
	line.len_tab = tgetnum ("it");
	nbr_line_for_malloc(&line, promt, pos_len, buf);
	pos->nbr_char = line.nbr_char;
	pos->nbr_cursor = line.nbr_cursor;
	pos->len = line.real;

	if ((ft_malloc_real_length(pos->nbr_cursor, pos->promt)) == 1)
		return (1);
	if ((ft_malloc_real_length(pos->nbr_cursor, pos->buf)) == 1)
		return (1);


	ft_memset(&line, 0, sizeof(t_calcul_len));
	line.co_max = tgetnum("co");
	line.len_tab = tgetnum ("it");
	ft_addvalue_lenbuf(pos, &line, promt, pos_len, buf);

/*
	int		x;
	fprintf(stderr, "pos->\n");
	fprintf(stderr, "\tco_max = [%d]\n", pos->co_max);
	fprintf(stderr, "\tlen = [%d]\n", pos->len);
	fprintf(stderr, "\tnbr_char = [%d]\n", pos->nbr_char);
	fprintf(stderr, "\tnbr_cursor = [%d]\n", pos->nbr_cursor);
	fprintf(stderr, "\tnbr_pos = [%d]\n", pos->nbr_pos);
	fprintf(stderr, "\tchar_pos = [%d]\n", pos->char_pos);
	fprintf(stderr, "\tcursor_pos = [%d]\n", pos->cursor_pos);
	x = 0;
	while (x <= pos->nbr_cursor)
	{
		fprintf(stderr, "\tbuf->pos_char[%d] = [%d]\n", x, pos->buf->pos_char[x]);
		fprintf(stderr, "\tbuf->pos_cursor[%d] = [%d]\n", x, pos->buf->pos_cursor[x]);
		fprintf(stderr, "\tpromt->pos_char[%d] = [%d]\n", x, pos->promt->pos_char[x]);
		fprintf(stderr, "\tpromt->pos_cursor[%d] = [%d]\n", x, pos->promt->pos_cursor[x]);
		x++;
	}
*/

	return (0);
}


int			refresh_size_win(t_promt promt, t_lchar *buf, int pos_buf, t_pos *pos)
{
	pos->co_max = tgetnum("co");
	pos->li_max = tgetnum("li");
	pos->len_tab = tgetnum ("it");
	real_length(pos, promt, pos_buf, buf);
	return (0);
}

void		replace_cursor(t_sequence *sequence, t_pos *pos, int mode)
{
	int		count_line;
	int		count_pos;

	if (mode == 0) // go to the new pos with pos at the start
	{
		count_line = 0;
		while (count_line <= pos->nbr_pos)
		{
			if (count_line < pos->nbr_pos)
				tputs(sequence->up_scroll, 0, f_putchar);
			count_line++;
		}
		count_pos = 0;
		tputs(sequence->go_start_line, 0, f_putchar);
		while (count_pos < pos->cursor_pos)
		{
			tputs(sequence->right_cursor, 0, f_putchar);
			count_pos++;
		}
	}
	else if (mode == 1) // go to the start with pos at the last pos know
	{
		tputs(sequence->go_start_line, 0, f_putchar);
		count_line = 0;
		while (count_line <= pos->nbr_pos)
		{
			if (count_line < pos->nbr_pos)
				tputs(sequence->down_scroll, 0, f_putchar);
			count_line++;
		}
	}
	else if (mode == 3) // go to the new_pos with pos at the end
	{
		count_line = pos->nbr_pos;
		while (count_line <= pos->nbr_char)
		{
			if (count_line < pos->nbr_char)
				tputs(sequence->down_scroll, 0, f_putchar);
			count_line++;
		}
		tputs(tgetstr("cr", NULL), 0, f_putchar);
		count_pos = 0;
		while (count_pos < pos->cursor_pos)
		{
			tputs(sequence->right_cursor, 0, f_putchar);
			count_pos++;
		}
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
	ft_memset(pos, 0, sizeof(t_pos));
	pos->co_max = tgetnum("co");
	pos->li_max = tgetnum("li");
	pos->len_tab = tgetnum ("it");
	pos->malloc = 1;
	pos->start = 0;
	pos->end = (pos->li_max - 1);
	pos->nbr_line_pos = 0;
	pos->nbr_line_len = 0;
	(void)type;
	return (0);
}

int		free_pos(t_pos *pos)
{
	free(pos->promt->pos_char);
	free(pos->promt->pos_cursor);
	free(pos->buf->pos_char);
	free(pos->buf->pos_cursor);
	free(pos->promt);
	free(pos->buf);
	return (0);
}

int				print_the_buf(t_sequence *sequence, t_promt promt, t_lchar *buf,
		t_pos *pos)
{
	int		count;
	int		upromt;
	int		ubuf;

	ubuf = 0;
	upromt = 0;
	count = 0;
	tputs(sequence->go_start_line, 0, f_putchar);
	tputs(sequence->clear_rest_screen, 0, f_putchar);
	while (count <= pos->nbr_char)
	{
		write(STDOUT_FILENO, promt.str + upromt, (pos->promt->pos_char[count]));
		write(STDOUT_FILENO, buf->c + ubuf, (pos->buf->pos_char[count]));
//		fprintf(stderr, "\033[33m");
//		write(STDERR_FILENO, promt.str + upromt, (pos->promt->pos_char[count]));
//		write(STDERR_FILENO, buf->c + ubuf, (pos->buf->pos_char[count]));
//		fprintf(stderr, "\033[0m\n");
		if (count < pos->nbr_char &&
				buf->c[upromt + pos->promt->pos_char[count]] != '\n' &&
				buf->c[ubuf + pos->buf->pos_char[count]] != '\n')
			tputs(sequence->up_scroll, 0, f_putchar);
		upromt += pos->promt->pos_char[count];
		ubuf += pos->buf->pos_char[count];
		count++;
	}
	replace_cursor(sequence, pos, 3);
	return (0);
}

t_lchar	*add_lchar(t_lchar *buf_start, t_lchar *buf_add)
{
	int		x;
	t_lchar	*new_buf;

	if ((new_buf = ft_memalloc(sizeof(t_lchar))) == NULL)
		return (NULL);
	new_buf->len = buf_start->len + buf_add->len + 1;
	if ((new_buf->c = ft_memalloc(sizeof(char) * new_buf->len + 1)) == NULL)
		return (NULL);
	if ((new_buf->type = ft_memalloc(sizeof(int) * new_buf->len + 1)) == NULL)
		return (NULL);
	x = 0;
	while (x < new_buf->len)
	{
		if (x < buf_start->len)
		{
			new_buf->c[x] = buf_start->c[x];
			new_buf->type[x] = buf_start->type[x];
		}
		else if (x == buf_start->len)
		{
			new_buf->c[x] = '\n';
			new_buf->type[x] = _NEW_LINE;
		}
		else
		{
			new_buf->c[x] = buf_add->c[(x - 1) - buf_start->len];
			new_buf->type[x] = buf_add->type[(x - 1) - buf_start->len];
		}
		x++;
	}
	return (new_buf);
}

int			verif_exit(t_lchar *buf)
{
	int			x;
	int			backslash;
	int			open_quote;
	int			open_double_quote;
	int			open_backquote;
	int			open_pipe;

	backslash = 0;
	open_pipe = 0;
	open_quote = 0;
	open_double_quote = 0;
	open_backquote = 0;
	x = 0;
	while (x < buf->len)
	{
		if (buf->type[x] == _BACKSLASH && backslash == 0 && open_quote == 0)
			backslash = ~backslash;
		else if (buf->type[x] == _APOSTROPHE && open_double_quote == 0)
			open_quote = ~open_quote;
		else if (buf->type[x] == _DOUBLE_QUOTE && open_backquote == 0 &&
				backslash == 0 && open_quote == 0)
			open_double_quote = ~open_double_quote;
		else if (buf->type[x] == _PRIME && backslash == 0 && open_quote == 0)
			open_backquote = ~open_backquote;
		else if (buf->type[x] == _PIPE && backslash == 0 && open_quote == 0 &&
				open_double_quote == 0)
			open_pipe = ~open_pipe;
		else if (backslash == -1 || open_quote == -1 || open_double_quote == -1)
		{
			if (open_backquote == 0)
				buf->type[x] = _ALPHA;
			backslash = 0;
		}
		else if (buf->type[x] != _SPACE)
			open_pipe = 0;
		x++;
	}
	if (open_backquote == -1 || backslash == -1 || open_quote == -1
			|| open_double_quote == -1 || open_pipe == -1)
		return (1);
	return (0);
}

int				free_history(t_history *history)
{
	int		x;

	x = 0;
	while (x < history->malloc)
	{
		if (x != history->pos_buf)
			free(history->buf[x]);
		x++;
	}
	free(history->buf);
	free(history->pos);
	return (1);
}

int				change_pos(int add_pos_buf, int type, int add_pos, t_history *hist)
{
	hist->pos_buf += add_pos_buf;
	if (type == 0)
		hist->pos[hist->pos_buf] += add_pos;
	if (type == 1)
		hist->pos[hist->pos_buf] = add_pos;
	return (0);
}

int				apply_arrow(t_sequence *sequence, int type, t_promt *promt, int which_arrow,
		t_history *hist, t_pos *pos)
{
	(void)type;
	(void)pos;
	if ((which_arrow == 65 && hist->pos_buf > 0) ||
			(which_arrow == 66 && hist->pos_buf < hist->len))
	{
		replace_cursor(sequence, pos, 1);
		if (which_arrow == 65)
			change_pos(-1, 1, hist->buf[hist->pos_buf - 1]->len, hist);
		else if (which_arrow == 66)// down
			change_pos(1, 1, hist->buf[hist->pos_buf + 1]->len, hist);
		refresh_size_win(promt[type], hist->buf[hist->pos_buf],
				hist->pos[hist->pos_buf], pos);
	}
	else if ((which_arrow == 67 &&
				hist->pos[hist->pos_buf] < hist->buf[hist->pos_buf]->len) ||
			(which_arrow == 68 && hist->pos[hist->pos_buf] > 0) ||
			(which_arrow == 70) ||
			(which_arrow == 72))
	{
		replace_cursor(sequence, pos, 1);
		if (which_arrow == 67) // right
			change_pos(0, 0, 1, hist);
		else if (which_arrow == 68) // left
			change_pos(0, 0, -1, hist);
		else if (which_arrow == 70) // end
			change_pos(0, 1, hist->buf[hist->pos_buf]->len, hist);
		else if (which_arrow == 72) // home
			change_pos(0, 1, 0, hist);
		refresh_size_win(promt[type], hist->buf[hist->pos_buf],
				hist->pos[hist->pos_buf], pos);
		replace_cursor(sequence, pos, 0);
	}
	return (0);
}

int				ft_arrow_left(t_sequence *sequence, t_pos *pos, t_promt promt,
		t_history *history)
{
	if (history->pos[history->pos_buf] > 0)
	{
		replace_cursor(sequence, pos, 1);
		history->pos[history->pos_buf]--;
		refresh_size_win(promt, history->buf[history->pos_buf],
				history->pos[history->pos_buf], pos);
		replace_cursor(sequence, pos, 0);
	}
	return (0);
}

int				ft_arrow_right(t_sequence *sequence, t_pos *pos, t_promt promt,
		t_history *history)
{
	if (history->pos[history->pos_buf] < history->buf[history->pos_buf]->len)
	{
		replace_cursor(sequence, pos, 1);
		history->pos[history->pos_buf]++;
		refresh_size_win(promt, history->buf[history->pos_buf],
				history->pos[history->pos_buf], pos);
		replace_cursor(sequence, pos, 0);
	}
	return (0);
}

int				ft_arrow_up(t_sequence *sequence, t_pos *pos, t_promt promt,
		t_history *history)
{
	if (history->pos_buf > 0)
	{
		replace_cursor(sequence, pos, 1);
		history->pos_buf--;
		history->pos[history->pos_buf] = history->buf[history->pos_buf]->len;
		refresh_size_win(promt, history->buf[history->pos_buf],
				history->pos[history->pos_buf], pos);
		print_the_buf(sequence, promt, history->buf[history->pos_buf], pos);
	}
	return (0);
}

int				ft_arrow_down(t_sequence *sequence, t_pos *pos, t_promt promt,
		t_history *history)
{
	if (history->pos_buf < history->len)
	{
		replace_cursor(sequence, pos, 1);
		history->pos_buf++;
		history->pos[history->pos_buf] = history->buf[history->pos_buf]->len;
		refresh_size_win(promt, history->buf[history->pos_buf],
				history->pos[history->pos_buf], pos);
		print_the_buf(sequence, promt, history->buf[history->pos_buf], pos);
	}
	return (0);
}

int				ft_home_position(t_sequence *sequence, t_pos *pos, t_promt promt,
		t_history *history)
{
	replace_cursor(sequence, pos, 1);
	history->pos[history->pos_buf] = 0;
	refresh_size_win(promt, history->buf[history->pos_buf],
			history->pos[history->pos_buf], pos);
	replace_cursor(sequence, pos, 0);
	return (0);
}

int				ft_home_down(t_sequence *sequence, t_pos *pos, t_promt promt,
		t_history *history)
{
	replace_cursor(sequence, pos, 1);
	history->pos[history->pos_buf] = history->buf[history->pos_buf]->len;
	refresh_size_win(promt, history->buf[history->pos_buf],
			history->pos[history->pos_buf], pos);
	replace_cursor(sequence, pos, 0);
	return (0);
}

int				ft_char_return(t_sequence *sequence, t_pos *pos,
		t_promt promt, t_history *history)
{
	refresh_size_win(promt, history->buf[history->pos_buf],
			history->pos[history->pos_buf], pos);
	print_the_buf(sequence, promt, history->buf[history->pos_buf], pos);
	write(0, "\n", 1);
	return (2);
}

int				ft_exit_edition_line(t_sequence *sequence, t_pos *pos,
		t_promt promt, t_history *history)
{
	(void)sequence;
	(void)pos;
	(void)promt;
	(void)history;
	if (history->buf[history->pos_buf]->len == 0)
		return (1);
	return (0);
}

int				ft_delete(t_sequence *sequence, t_pos *pos,
		t_promt promt, t_history *history)
{
	int		x;
	char	tmp_c;
	int		tmp_type;

	if ((history->pos[history->pos_buf]) > 0)
	{
		replace_cursor(sequence, pos, 1);
		history->pos[history->pos_buf]--;
		x = history->pos[history->pos_buf];
		while (x < history->buf[history->pos_buf]->len)
		{
			tmp_c = history->buf[history->pos_buf]->c[x + 1];
			history->buf[history->pos_buf]->c[x] = tmp_c;
			tmp_type = history->buf[history->pos_buf]->type[x + 1];
			history->buf[history->pos_buf]->type[x] = tmp_type;
			x++;
		}
		history->buf[history->pos_buf]->len--;
		ft_addtype(history->buf[history->pos_buf],
				history->pos[history->pos_buf],
				history->buf[history->pos_buf]->len);
		refresh_size_win(promt, history->buf[history->pos_buf],
				history->pos[history->pos_buf], pos);
		print_the_buf(sequence, promt, history->buf[history->pos_buf], pos);
	}
	return (0);
}

int				ft_delete_char(t_sequence *sequence, t_pos *pos,
		t_promt promt, t_history *history)
{
	int		x;
	char	tmp_c;
	int		tmp_type;

	if (history->pos[history->pos_buf] < history->buf[history->pos_buf]->len)
	{
		replace_cursor(sequence, pos, 1);
		x = history->pos[history->pos_buf];
		while (x < history->buf[history->pos_buf]->len)
		{
			tmp_c = history->buf[history->pos_buf]->c[x + 1];
			history->buf[history->pos_buf]->c[x] = tmp_c;
			tmp_type = history->buf[history->pos_buf]->type[x + 1];
			history->buf[history->pos_buf]->type[x] = tmp_type;
			x++;
		}
		history->buf[history->pos_buf]->len--;
		ft_addtype(history->buf[history->pos_buf],
				history->pos[history->pos_buf],
				history->buf[history->pos_buf]->len);
		refresh_size_win(promt, history->buf[history->pos_buf],
				history->pos[history->pos_buf], pos);
		print_the_buf(sequence, promt, history->buf[history->pos_buf], pos);
	}
	return (0);
}


t_which_key		which_key[] = {
	{"char_return", ft_char_return},
	{"exit", ft_exit_edition_line},
	{"delete", ft_delete},
	{"left_arrow", ft_arrow_left},
	{"right_arrow", ft_arrow_right},
	{"up_arrow", ft_arrow_up},
	{"down_arrow", ft_arrow_down},
	{"home_position", ft_home_position},
	{"home_down", ft_home_down},
	{"backspace", NULL},
	{"clear_all_the_tabs", NULL},
	{"clear_tab_column", NULL},
	{"clear_the_screen", NULL},
	{"delete_char", ft_delete_char},
	{"delete_the_line", NULL},
	{"exit_insert", NULL},
	{"clear_end_line", NULL},
	{"clear_end_sreen", NULL},
	{"insert_char", NULL},
	{"insert_the_line", NULL},
	{"next_line", NULL},
	{"previous_page", NULL},
	{"forward_scroll", NULL},
	{"reverse_scroll", NULL},
	{"set_tab_column", NULL},
	{NULL, NULL}
};


t_lchar			*line_edition(int type, t_history *history)
{
	char			buffer[4095];
	t_pos			pos;
	int				ret;
	int				ret_f;
	t_lchar			*buf;
	t_lchar			*tmp_buf;
	t_lchar			*new_buf;
	t_key			key[25];
	t_sequence		sequence;
	int				count_buffer;

	t_promt			promt[] = {
		{LEN_PROMT_EDIT, PROMT_EDIT},
		{LEN_PROMT_HER, PROMT_HER},
		{LEN_PROMT_HER, PROMT_HER}
	};

	if (ft_init_termcaps(key, &sequence) == 1)
		return (NULL);
	if (creat_struct_pos(type, &pos) == 1)
		return (NULL);
	write(1, PROMT, LEN_PROMT);
	refresh_size_win(promt[type], history->buf[history->pos_buf],
			history->pos[history->pos_buf], &pos);
	while (1)
	{
		ft_memset(&buffer, 0, sizeof(char) * 4);
		ret = read(STDIN_FILENO, buffer, 4095);
		buffer[ret] = '\0';

/*
		int		print = 0;

		fprintf(stderr, "\033[31mret = [%d]\n", ret);
		while (print < ret)
		{
			fprintf(stderr, "[%d]", buffer[print]);
			print++;
		}
		fprintf(stderr, "\033[0m\n");
*/

		if (g_sig == SIGINT)
		{
			g_sig = 0;
			history->buf[history->pos_buf]->len = -1;
			write(1, "\n", 1);
			break ;
		}
		count_buffer = 0;
//		fprintf(stderr, "\n");
		ret_f = 0;
		while (count_buffer < ret)
		{
			int		count_key = 0;
			int		count_len_key = 0;
			int		len_key = 0;
			while (which_key[count_key].key != NULL)
			{
//				fprintf(stderr, "key[%d] = {[%s] = ", count_key, which_key[count_key].key);
				if (key[count_key].str != NULL)
				{
					len_key = ft_strlen(key[count_key].str);
					count_len_key = 0;
					while (count_len_key < len_key)
					{
//						fprintf(stderr, "[%d]", key[count_key].str[count_len_key]);
						count_len_key++;
					}
					if (ft_strmatch(key[count_key].str, buffer + count_buffer) == 1)
					{
						ret_f = which_key[count_key].f(&sequence, &pos, promt[type], history);
//						fprintf(stderr, " or ");
						count_len_key = 0;
						while (count_len_key < len_key)
						{
//							if (ft_isprint(key[count_key].str[count_len_key]))
//								fprintf(stderr, "[%c]", key[count_key].str[count_len_key]);
//							else
//								fprintf(stderr, "[%d]", key[count_key].str[count_len_key]);
							count_len_key++;
						}
						count_buffer += ft_strlen(key[count_key].str);
//						fprintf(stderr, "}\n");
						break ;
					}
					else
						count_key++;
				}
				else
					count_key++;
//				fprintf(stderr, "}\n");
			}
//			fprintf(stderr, "ref_f == [%d]\n", ret_f);
			if (ret_f == 1)
			{
				creat_buf(history, buffer, ret);
				break ;
			}
			else if (ret_f == 2)
			{
				break ;
			}
			else if (which_key[count_key].key == NULL)
			{
//				fprintf(stderr, "c'est pas une commande\n");
				replace_cursor(&sequence, &pos, 1);
				creat_buf(history, buffer, 1);
				refresh_size_win(promt[type], history->buf[history->pos_buf],
						history->pos[history->pos_buf], &pos);
				print_the_buf(&sequence, promt[type], history->buf[history->pos_buf], &pos);
			}
			else
			{
//				fprintf(stderr, "c'est une commande\n");
			}
			count_buffer++;
		}
//		fprintf(stderr, "ref_f == [%d]\n", ret_f);
		if (ret_f == 1 || ret_f == 2)
		{
			break ;
		}
	}
	if (ft_reset_termcaps(&sequence) == 1)
		return (NULL);
	if ((buf = ft_memalloc(sizeof(t_lchar) + 1)) == NULL)
		return (NULL);
	ft_lchardup(buf, history->buf[history->pos_buf], 0);
	if (type == 0)
	{
		while (verif_exit(buf) == 1)
		{
			tmp_buf = while_main(1, history);
			if (tmp_buf->len != -1)
			{
				new_buf = add_lchar(buf, tmp_buf);
				buf = new_buf;
			}
			else
			{
				free_pos(&pos);
				return (tmp_buf);
			}
		}
	}
	free_pos(&pos);
	return (buf);
}
