#include "../../include/line_edition.h"
#include "../../include/ft_termcaps.h"
#include "../../include/history.h"
#include "../../include/vingt_et_un_sh.h"
#include "../../include/parser.h"
#include <stdio.h>

char PC;   /* For tputs.  */
char *BC;  /* For tgoto.  */
char *UP;


int			ft_freelchar(t_lchar *buf)
{
	free(buf->c);
	free(buf->type);
	return (0);
}

int			ft_remalloc_buf(t_history *history, int ret)
{
	t_lchar		new_buf;

//	fprintf(stderr, "history->buf[history->pos_buf]->len = [%d], ret = [%d]\n",
//			history->buf[history->pos_buf]->len, ret);
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
//	fprintf(stderr, "promt_char = [%d], promt_cursor = [%d]\n", promt_char, promt_cursor);
//	fprintf(stderr, "line->count = [%d], line->start_char = [%d]\n", line->count, line->start_char);
//	fprintf(stderr, "line->real = [%d], line->start_cursor = [%d]\n", line->real, line->start_cursor);
//	fprintf(stderr, "str[%d - %d] = [%c]\n", line->count, promt_char, str[line->count - promt_char]);
	(void)pos;
	(void)promt_char;
	(void)promt_cursor;
	if (str[line->count - line->len_promt] == 9)
	{
		line->count++;
		line->len = (line->real - line->start_cursor);
		pos->pos_char[line->nbr_cursor] = (line->count - line->start_char) - promt_char;
		pos->pos_cursor[line->nbr_cursor] = (line->len - promt_cursor);
//		fprintf(stderr, "line->len = [%d], line->co_max = [%d]\n", line->len, line->co_max);
//		fprintf(stderr, "line->real = [%d], line->start_cursor = [%d]\n", line->real, line->start_cursor);
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
//	fprintf(stderr, "promt_char = [%d], promt_cursor = [%d]\n", promt_char, promt_cursor);
//	fprintf(stderr, "line->count = [%d], line->start_char = [%d]\n", line->count, line->start_char);
//	fprintf(stderr, "line->real = [%d], line->start_cursor = [%d]\n", line->real, line->start_cursor);
	(void)promt_char;
	(void)promt_cursor;
	line->len = (line->real - line->start_cursor);
	pos->pos_char[line->nbr_cursor] = (line->count - line->start_char) - promt_char;
	pos->pos_cursor[line->nbr_cursor] = (line->len - promt_cursor);
//	fprintf(stderr, "	line->len = \033[35m[%d]\033[0m >= line->co_max = \033[35m[%d]\033[0m\n", line->len, line->co_max);
//	fprintf(stderr, "	line->real = [%d], line->start_cursor = [%d]\n", line->real, line->start_cursor);
//	fprintf(stderr, "	line->count = [%d], line->start_char = [%d]\n", line->count, line->start_char);
//		fprintf(stderr, "	pos->pos_char[%d] = \033[31m[%d]\033[0m, pos->pos_cursor[%d] = \033[31m[%d]\033[0m\n", line->nbr_cursor, pos->pos_char[line->nbr_cursor], line->nbr_cursor, pos->pos_cursor[line->nbr_cursor]);
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
//	fprintf(stderr, "promt->len = [%d], buf->len = [%d]\n", promt->len, buf->len);
	while (line->count < promt.len + buf->len)
	{
//		fprintf(stderr, "line->count = [%d], promt->len + buf->len = [%d]\n", line->count, promt->len + buf->len);
		if (line->count < promt.len)
		{
//			fprintf(stderr, "1 line->count = [%d], line->real = [%d], str[%d] = \033[32m[%c]\033[0m\n", line->count, line->real, line->count, promt.str[line->count]);
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
//			fprintf(stderr, "2 line->count = [%d], line->real = [%d], str[%d] = \033[32m[%c]\033[0m\n", line->count, line->real, line->count - promt.len, buf->c[line->count - promt.len]);
//			fprintf(stderr, "pos->promt->pos_char = [%d]\n", pos->promt->pos_char[line->nbr]);
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
//			fprintf(stderr, "3 line->count = [%d], line->real = [%d], str[%d] = \033[32m[%c]\033[0m\n", line->count, line->real, line->count - promt.len, buf->c[line->count - promt.len]);
//			fprintf(stderr, "pos->promt->pos_char = [%d]\n", pos->promt->pos_char[line->nbr]);
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
//;	int		count;

	if (struc->pos_char != NULL)
		free(struc->pos_char);
	if ((struc->pos_char = ft_memalloc(sizeof(t_length) * (len + 1))) == NULL)
		return (1);
//	count = 0;
//	while (count <= len)
//	{
//		struc->pos_char[count] = -1;
//		count++;
//	}
	if (struc->pos_cursor != NULL)
		free(struc->pos_cursor);
	if ((struc->pos_cursor = ft_memalloc(sizeof(t_length) * (len + 1))) == NULL)
		return (1);
//	count = 0;
//	while (count <= len)
//	{
//		struc->pos_cursor[count] = -1;
//		count++;
//	}
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

//	fprintf(stderr, "pos->nbr_char = [%d], pos->nbr_cursor = [%d]\n", line.nbr_char, line.nbr_cursor);
	pos->nbr_char = line.nbr_char;
	pos->nbr_cursor = line.nbr_cursor;
	pos->len = line.real;

	if ((ft_malloc_real_length(pos->nbr_cursor, pos->promt)) == 1)
		return (1);
	if ((ft_malloc_real_length(pos->nbr_cursor, pos->buf)) == 1)
		return (1);


//	x = 0;
//	while (x <= pos->nbr)
//	{
//		fprintf(stderr, "\tbuf->pos_char[%d] = [%d]\n", x, pos->buf->pos_char[x]);
//		fprintf(stderr, "\tbuf->pos_cursor[%d] = [%d]\n", x, pos->buf->pos_cursor[x]);
//		fprintf(stderr, "\tpromt->pos_char[%d] = [%d]\n", x, pos->promt->pos_char[x]);
//		fprintf(stderr, "\tpromt->pos_cursor[%d] = [%d]\n", x, pos->promt->pos_cursor[x]);
//		x++;
//	}

	ft_memset(&line, 0, sizeof(t_calcul_len));
	line.co_max = tgetnum("co");
	line.len_tab = tgetnum ("it");
	ft_addvalue_lenbuf(pos, &line, promt, pos_len, buf);

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
			{
				//	tputs(tgetstr("do", NULL), 0, f_putchar);
				//tputs(tgetstr("sf", NULL), 0, f_putchar);
				tputs(sequence->up_scroll, 0, f_putchar);
			}
			count_line++;
		}
		count_pos = 0;
//		fprintf(stderr, "count_line = [%d]\n", count_line);
		while (count_pos < pos->cursor_pos)
		{
//			fprintf(stderr, "test\n");
//			tputs(tgetstr("nd", NULL), 0, f_putchar);
			tputs(sequence->right_cursor, 0, f_putchar);
			count_pos++;
		}
	}
	else if (mode == 1) // go to the start with pos at the last pos know
	{
		tputs(tgetstr("cr", NULL), 0, f_putchar);
		tputs(sequence->go_start_line, 0, f_putchar);
		count_line = 0;
//		fprintf(stderr, "replace_cursor mode = 1\n");
		while (count_line <= pos->nbr_pos)
		{
//			fprintf(stderr, "count_line[%d] < pos->nbr[%d]\n", count_line, pos->nbr_cursor);
			if (count_line < pos->nbr_pos)
			{
//				fprintf(stderr, "\t\t`sr'\n");
				//	tputs(tgetstr("up", NULL), 0, f_putchar);
				//tputs(tgetstr("sr", NULL), 0, f_putchar);
				tputs(sequence->down_scroll, 0, f_putchar);
			}
			count_line++;
		}
	}
	else if (mode == 2) // go to the start with pos at the end
	{
/*		tputs(tgetstr("cr", NULL), 0, f_putchar);
		count_line = 0;
		while (count_line < pos->nbr_line_len)
		{
			if (count_line >= pos->start && count_line < pos->end)
			{
				//	tputs(tgetstr("up", NULL), 0, f_putchar);
				tputs(tgetstr("sr", NULL), 0, f_putchar);
			}
			count_line++;
		}
*/	}
	else if (mode == 3) // go to the new_pos with pos at the end
	{
		count_line = pos->nbr_pos;
		while (count_line <= pos->nbr_char)
		{
			if (count_line < pos->nbr_char)
			{
			//	tputs(tgetstr("up", NULL), 0, f_putchar);
			//	tputs(tgetstr("sr", NULL), 0, f_putchar);
				tputs(sequence->down_scroll, 0, f_putchar);
			}
			count_line++;
		}
		tputs(tgetstr("cr", NULL), 0, f_putchar);
		count_pos = 0;
		while (count_pos < pos->cursor_pos)
		{
	//		tputs(tgetstr("nd", NULL), 0, f_putchar);
			tputs(sequence->right_cursor, 0, f_putchar);
			count_pos++;
		}
	}
	else if (mode == 4) // go to the end with pos at the last pos know
	{
/*		count_line = pos->nbr_line_pos;
		while (count_line < pos->nbr_line_len)
		{
			if (count_line >= pos->start && count_line < pos->end)
			{
				//	tputs(tgetstr("do", NULL), 0, f_putchar);
				tputs(tgetstr("sf", NULL), 0, f_putchar);
			}
			count_line++;
		}
		tputs(tgetstr("cr", NULL), 0, f_putchar);
		count_pos = 0;
		while (count_pos < (pos->buf_pos.pos_cursor[pos->nbr_line_len] +
					pos->promt->pos_cursor[pos->nbr_line_len]))
		{
			tputs(tgetstr("nd", NULL), 0, f_putchar);
			count_pos++;
		}
*/	}
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
	//	real_length_promt(type, pos);
/*	pos->buf_pos.len = 0;
	pos->buf_pos.nbr= 0;
	if ((pos->buf_pos.pos_cursor = ft_memalloc(sizeof(int) *
					pos->malloc)) == NULL)
		return (1);
	if ((pos->buf_pos.pos_char = ft_memalloc(sizeof(int) *
					pos->malloc)) == NULL)
		return (1);
	pos->buf_len.len = 0;
	pos->buf_len.nbr = 0;
	if ((pos->buf_len.pos_cursor = ft_memalloc(sizeof(int) *
					pos->malloc)) == NULL)
		return (1);
	if ((pos->buf_len.pos_char = ft_memalloc(sizeof(int) *
					pos->malloc)) == NULL)
		return (1);
*/	return (0);
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

int				print_the_buf(t_sequence *sequence, t_promt promt,
		t_lchar *buf, int pos_buf, t_pos *pos)
{
	int		x;
	int		len_use_promt;
	int		len_use_buf;

	(void)pos_buf;
//	replace_cursor(pos, 1);
//	refresh_size_win(type, buf, pos_buf, pos);
	x = 0;
	len_use_buf = 0;
	len_use_promt = 0;
	tputs(sequence->clear_rest_screen, 0, f_putchar);
	while (x <= pos->nbr_char)
	{
		write(STDOUT_FILENO, promt.str + len_use_promt, (pos->promt->pos_char[x]));
		write(STDOUT_FILENO, buf->c + len_use_buf, (pos->buf->pos_char[x]));
//		fprintf(stderr, "len_use_promt = [%d]\n", len_use_promt);
//		fprintf(stderr, "promt->pos_char[%d] = [%d]\n", x, pos->promt->pos_char[x]);
//		fprintf(stderr, "len_use_buf = [%d]\n", len_use_buf);
//		fprintf(stderr, "buf->pos_char[%d] = [%d]\n", x, pos->buf->pos_char[x]);

//		fprintf(stderr, "\033[33m");
//		write(STDERR_FILENO, PROMT + len_use_promt, (pos->promt->pos_char[x]));
//		write(STDERR_FILENO, buf->c + len_use_buf, (pos->buf->pos_char[x]));
//		fprintf(stderr, "\033[0m\n");
//		fprintf(stderr, "buf = [%c]\n",
//				buf->c[len_use_buf + pos->buf->pos_char[x]]);
		if (x < pos->nbr_char &&
				buf->c[len_use_promt + pos->promt->pos_char[x]] != '\n' &&
				buf->c[len_use_buf + pos->buf->pos_char[x]] != '\n')
		{
//			fprintf(stderr, "next_line\n");
//			tputs(tgetstr("do", NULL), 0, f_putchar);
//			tputs(tgetstr("sf", NULL), 0, f_putchar);
			tputs(sequence->up_scroll, 0, f_putchar);
		}
		len_use_promt += pos->promt->pos_char[x];
		len_use_buf += pos->buf->pos_char[x];
		x++;
	}
//	refresh_size_win(type, buf, pos_buf, pos);
	replace_cursor(sequence, pos, 3);
/*
	while (x < pos->start)
	{
		len_use_promt += pos->promt.pos_char[x];
		len_use_buf += pos->buf_len.pos_char[x];
		x++;
	}
	tputs(tgetstr("cd", NULL), 0, f_putchar);
	x = 0;
	len_use_promt = 0;
	while (x <= pos->promt.nbr)
	{
		write(STDOUT_FILENO, PROMT + len_use_promt, pos->promt.pos_char[x]);
		len_use_promt += pos->promt.pos_char[x];
		if (x < pos->promt.nbr)
			tputs(tgetstr("sf", NULL), 0, f_putchar);
		x++;
	}
	x = 0;
	len_use_buf = 0;
	while (x <= pos->buf_len.nbr)
	{
		write(STDOUT_FILENO, buf->c + len_use_buf, pos->buf_len.pos_char[x]);
		len_use_buf += pos->buf_len.pos_char[x];
		if (x < pos->buf_len.nbr)
			tputs(tgetstr("sf", NULL), 0, f_putchar);
		x++;
	}
*/;/*
	   while (x <= pos->nbr_line_len && x <= pos->end)
	   {
	   write(STDOUT_FILENO, PROMT + len_use_promt, pos->promt.pos_char[x]);
	   write(STDOUT_FILENO, buf->c + len_use_buf, pos->buf_len.pos_char[x]);
	   len_use_promt += pos->promt.pos_char[x];
	   len_use_buf += pos->buf_len.pos_char[x];
	   if ((pos->promt.pos_char[pos->nbr_line_pos] +
	   pos->buf_len.pos_char[pos->nbr_line_pos]) >= pos->co_max &&
	   pos->nbr_line_pos < pos->malloc && x < pos->nbr_line_len &&
	   x < pos->end)
	   {
	//	fprintf(stderr, "test\n");
	//	tputs(tgetstr("do", NULL), 0, f_putchar);
	tputs(tgetstr("sf", NULL), 0, f_putchar);
	}
	x++;
	}
	*/
	return (0);
}

void	ft_printf_lchar(t_lchar *buf)
{
	int		x;
	char	*nbr;

	x = 0;
	while (x < buf->len)
	{
		write(1, "buf = [", 7);
		nbr = ft_itoa(x);
		write(1, nbr, ft_strlen(nbr));
		free(nbr);
		write(1, "], [", 4);
		write(1, buf->c + x, 1);
		write(1, "], [", 4);
		nbr = ft_itoa(buf->type[x]);
		write(1, nbr, ft_strlen(nbr));
		free(nbr);
		write(1, "], [", 4);
		write(1, which_define(buf->type[x]),
				ft_strlen(which_define(buf->type[x])));
		write(1, "]\n", 2);
		x++;
	}
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
//		replace_cursor(pos, 0);
//		print_the_buf(sequence, type, promt, hist->buf[hist->pos_buf],
//				hist->pos[hist->pos_buf], pos);
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
		refresh_size_win(promt, history->buf[history->pos_buf],
				history->pos[history->pos_buf], pos);
		replace_cursor(sequence, pos, 0);
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
		refresh_size_win(promt, history->buf[history->pos_buf],
				history->pos[history->pos_buf], pos);
		replace_cursor(sequence, pos, 0);
	}
	return (0);
}

int				ft_char_return(t_sequence *sequence, t_pos *pos,
		t_promt promt, t_history *history)
{
	(void)sequence;
	(void)pos;
	(void)promt;
	(void)history;
	return (1);
}

int				ft_exit_edition_line(t_sequence *sequence, t_pos *pos,
		t_promt promt, t_history *history)
{
	(void)sequence;
	(void)pos;
	(void)promt;
	(void)history;
	return (1);
}

int				ft_backspace(t_sequence *sequence, t_pos *pos,
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
		print_the_buf(sequence, promt, history->buf[history->pos_buf],
				history->pos[history->pos_buf], pos);
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
		print_the_buf(sequence, promt, history->buf[history->pos_buf],
				history->pos[history->pos_buf], pos);
	}
	return (0);
}


t_which_key		which_key[] = {
	{"char_return", ft_char_return},
	{"exit", ft_exit_edition_line},
	{"left_arrow", ft_arrow_left},
	{"right_arrow", ft_arrow_right},
	{"up_arrow", ft_arrow_up},
	{"down_arrow", ft_arrow_down},
	{"home_position", NULL},
	{"home_down", NULL},
	{"backspace", ft_backspace},
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
	t_key			key[24];
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
		if (g_sig == SIGINT)
		{
			g_sig = 0;
			history->buf[history->pos_buf]->len = -1;
			write(1, "\n", 1);
			break ;
		}
		count_buffer = 0;
		fprintf(stderr, "\n");
		ret_f = 0;
		while (count_buffer < ret)
		{
			int		count_key = 0;
			int		count_len_key = 0;
			int		len_key = 0;
			while (which_key[count_key].key != NULL)
			{
				fprintf(stderr, "key[%d] = {[%s] = ", count_key, which_key[count_key].key);
				if (key[count_key].str != NULL)
				{
					len_key = ft_strlen(key[count_key].str);
					count_len_key = 0;
					while (count_len_key < len_key)
					{
						fprintf(stderr, "[%d]", key[count_key].str[count_len_key]);
						count_len_key++;
					}
					if (ft_strmatch(key[count_key].str, buffer + count_buffer) == 1)
					{
						ret_f = which_key[count_key].f(&sequence, &pos, promt[type], history);
						fprintf(stderr, " or ");
						count_len_key = 0;
						while (count_len_key < len_key)
						{
							if (ft_isprint(key[count_key].str[count_len_key]))
								fprintf(stderr, "[%c]", key[count_key].str[count_len_key]);
							else
								fprintf(stderr, "[%d]", key[count_key].str[count_len_key]);
							count_len_key++;
						}
						count_buffer += ft_strlen(key[count_key].str);
						fprintf(stderr, "}\n");
						fprintf(stderr, "allo ??\n");
						break ;
						fprintf(stderr, "c'est possible ??\n");
					}
					else
						count_key++;
				}
				else
					count_key++;
				fprintf(stderr, "}\n");
			}
			fprintf(stderr, "ref_f == [%d]\n", ret_f);
			if (ret_f == 1)
			{
//				replace_cursor(&sequence, &pos, 1);
				creat_buf(history, buffer, ret);
//				refresh_size_win(promt[type], history->buf[history->pos_buf],
//						history->pos[history->pos_buf], &pos);
//				print_the_buf(&sequence, type, promt, history->buf[history->pos_buf],
//						history->pos[history->pos_buf], &pos);
				break ;
			}
			else if (which_key[count_key].key == NULL)
			{
				fprintf(stderr, "c'est pas une commande\n");
				replace_cursor(&sequence, &pos, 1);
				creat_buf(history, buffer, 1);
				refresh_size_win(promt[type], history->buf[history->pos_buf],
						history->pos[history->pos_buf], &pos);
				print_the_buf(&sequence, promt[type], history->buf[history->pos_buf],
						history->pos[history->pos_buf], &pos);
			}
			else
			{
				fprintf(stderr, "c'est une commande\n");
			}
			count_buffer++;
		}
		fprintf(stderr, "ref_f == [%d]\n", ret_f);
		if (ret_f == 1 || ret_f == 2)
		{
			break ;
		}
/*
		int		print = 0;

		fprintf(stderr, "ret = [%d]\n", ret);
		while (print < ret)
		{
			fprintf(stderr, "[%d]", buffer[print]);
			print++;
		}
		fprintf(stderr, "\n");
*/
/*
		if (g_sig == SIGINT)
		{
			g_sig = 0;
			history->buf[history->pos_buf]->len = -1;
			write(1, "\n", 1);
			break ;
		}
		if (buffer[0] == 4 && ret == 1 &&
				history->buf[history->pos_buf]->len == 0 && type == 0)
		{
			creat_buf(history, buffer, ret);
			break ;
		}
		else if (buffer[0] == 4 && ret == 1)
		{
			replace_cursor(&sequence, &pos, 1);
			delete_key(history);
			refresh_size_win(promt[type], history->buf[history->pos_buf],
					history->pos[history->pos_buf], &pos);
			print_the_buf(&sequence, type, promt, history->buf[history->pos_buf],
					history->pos[history->pos_buf], &pos);
		}
		else if (buffer[0] == 127 && ret == 1)
		{
			replace_cursor(&sequence, &pos, 1);
			backspace_key(history);
			refresh_size_win(promt[type], history->buf[history->pos_buf],
					history->pos[history->pos_buf], &pos);
			print_the_buf(&sequence, type, promt, history->buf[history->pos_buf],
					history->pos[history->pos_buf], &pos);
		}
		else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 51)
		{
			replace_cursor(&sequence, &pos, 1);
			delete_key(history);
			refresh_size_win(promt[type], history->buf[history->pos_buf],
					history->pos[history->pos_buf], &pos);
			print_the_buf(&sequence, type, promt, history->buf[history->pos_buf],
					history->pos[history->pos_buf], &pos);
		}
		else if (buffer[0] == 27 && buffer[1] == 91)
			apply_arrow(&sequence, type, promt, buffer[2], history, &pos);
		else if (buffer[0] == 10 && ret == 1)
		{
			change_pos(0, 1, history->buf[history->pos_buf]->len, history);
//			print_the_buf(type, history->buf[history->pos_buf],
//					history->pos[history->pos_buf], &pos);
			write(1, "\n", 1);
			break ;
		}
		else
		{
			replace_cursor(&sequence, &pos, 1);
			creat_buf(history, buffer, ret);
			refresh_size_win(promt[type], history->buf[history->pos_buf],
					history->pos[history->pos_buf], &pos);
			print_the_buf(&sequence, type, promt, history->buf[history->pos_buf],
					history->pos[history->pos_buf], &pos);
		}
*/
	}
	if (ft_reset_termcaps(&sequence) == 1)
		return (NULL);
	if ((buf = ft_memalloc(sizeof(t_lchar) + 1)) == NULL)
		return (NULL);
	ft_lchardup(buf, history->buf[history->pos_buf], 0);
	//	ft_printf_lchar(buf);
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
