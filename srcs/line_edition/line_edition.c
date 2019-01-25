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
	history->len[history->pos_buf]++;
	return (0);
}

int			remalloc_struct_pos(t_pos *pos, int new_li)
{
	int		*tmp_pos_act;
	int		*tmp_pos_buf;
	int		*tmp_pos_len;
	int		*tmp_pos_promt;

	if ((tmp_pos_act = ft_memalloc(sizeof(int) * new_li + 1)) == NULL)
		return (1);
	if ((tmp_pos_buf = ft_memalloc(sizeof(int) * new_li + 1)) == NULL)
		return (1);
	if ((tmp_pos_len = ft_memalloc(sizeof(int) * new_li + 1)) == NULL)
		return (1);
	if ((tmp_pos_promt = ft_memalloc(sizeof(int) * new_li + 1)) == NULL)
		return (1);
	pos->li_max = new_li;
	free(pos->pos_act);
	pos->pos_act = tmp_pos_act;
	free(pos->pos_buf);
	pos->pos_buf = tmp_pos_buf;
	free(pos->pos_len);
	pos->pos_len = tmp_pos_len;
	free(pos->pos_promt);
	pos->pos_len = tmp_pos_promt;
	return (0);
}

int			add_the_pos_buf(t_pos *pos, int count_tab, char *str, int len)
{
	int		count_len;
	int		len_use;
	int		length;
	int		nbr_line;
	int		line_len;
	int		next_tab;

	len_use = 0;
	length = 0;
	line_len = 0;
	nbr_line = 0;
	count_len = 0;
	fprintf(stderr, "	creat		change\n");
	while (count_len < len)
	{
		if (str[count_len] == 9)
		{
			line_len = (count_tab + length) - (pos->co_max * nbr_line);
			next_tab = ((line_len + pos->len_tab) / pos->len_tab) * pos->len_tab;
			if (next_tab > pos->co_max)
				next_tab = pos->co_max;
			length = (next_tab - count_tab) + (pos->co_max * nbr_line);
		}
		else
			length++;
		fprintf(stderr, "	creat	len_use = [%d]\n", len_use);
		pos->pos_buf[nbr_line] = ((count_len + 1) - len_use);
		fprintf(stderr, "	creat	pos.pos_buf[%d] = [%d]\n", nbr_line, pos->pos_buf[nbr_line]);
		if ((count_tab + length) >= (pos->co_max * (nbr_line + 1)))
		{
			len_use = (count_len + 1);
			nbr_line++;
		}
		count_len++;
	}
	return (length);

}

int			real_length(t_pos *pos, int count_tab, char *str, int len)
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
			next_tab = ((line_len + pos->len_tab) / pos->len_tab) * pos->len_tab;
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

int			refresh_size_win(int type, t_history *history, t_pos *pos)
{
	int		tmp_co_max;
	int		tmp_li_max;
	int		count_pos;
	int		count_line;
	int		real_length_promt;

	tmp_co_max = tgetnum("co") - 1;
	tmp_li_max = tgetnum("li");
	if (tmp_co_max != pos->co_max)
		pos->co_max = tmp_co_max;;
	if (tmp_li_max != pos->li_max)
		if (remalloc_struct_pos(pos, tmp_li_max) == 1)
			return (1);
	count_line = 0;
	real_length_promt = real_length(pos, 0, PROMT, LEN_PROMT);
	count_pos = real_length_promt;
	while (count_pos >= 0)
	{
		if (count_pos - pos->co_max >= 0)
			pos->pos_promt[count_line] = pos->co_max;
		else
			pos->pos_promt[count_line] = count_pos;
		count_pos = count_pos - pos->co_max;
		count_line++;
	}
	count_line = 0;
	count_pos = real_length(pos, real_length_promt,
			history->buf[history->pos_buf], history->pos[history->pos_buf]);
	while (count_pos >= 0)
	{
		fprintf(stderr, "count_pos = [%d]\n", count_pos);
		if (count_pos - (pos->co_max - pos->pos_promt[count_line]) >= 0)
			pos->pos_act[count_line] = (pos->co_max - pos->pos_promt[count_line]);
		else
			pos->pos_act[count_line] = count_pos;
		count_pos = count_pos - (pos->co_max - pos->pos_promt[count_line]);
		count_line++;
	}
	count_line = 0;
	count_pos = real_length(pos, real_length_promt,
			history->buf[history->pos_buf], (history->len[history->pos_buf] - 1));
	while (count_pos >= 0)
	{
		if (count_pos - (pos->co_max - pos->pos_promt[count_line]) >= 0)
			pos->pos_len[count_line] = (pos->co_max -
					pos->pos_promt[count_line]);
		else
			pos->pos_len[count_line] = count_pos;
		count_pos = count_pos - (pos->co_max - pos->pos_promt[count_line]);
		count_line++;
	}
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
		while ((pos->pos_act[count_line] + pos->pos_promt[count_line]) == pos->co_max)
		{
			fprintf(stderr, "	(0)	nbr of `do' [%d] = [%d]\n",
					pos->pos_act[count_line] + pos->pos_promt[count_line], pos->co_max);
			tputs(tgetstr("do", NULL), 0, f_putchar);
			count_line++;
		}
		count_pos = 0;
		fprintf(stderr, "	(0)	nbr of `nd' = [%d]\n",
				pos->pos_act[count_line] + pos->pos_promt[count_line]);
		while (count_pos < (pos->pos_act[count_line] + pos->pos_promt[count_line]))
		{
			tputs(tgetstr("nd", NULL), 0, f_putchar);
			count_pos++;
		}
	}
	else if (mode == 1) // go to the start with pos at the last pos know
	{
		count_line = 0;
		fprintf(stderr, "	(1)	nbr of `up' [%d] = [%d]\n",
				pos->pos_act[count_line] + pos->pos_promt[count_line], pos->co_max);
		while ((pos->pos_act[count_line] + pos->pos_promt[count_line]) == pos->co_max)
		{
			tputs(tgetstr("up", NULL), 0, f_putchar);
			count_line++;
		}
		tputs(tgetstr("cr", NULL), 0, f_putchar);
	}
	else if (mode == 2) // go to the start with pos at the end
	{
		count_line = 0;
		fprintf(stderr, "	(2)	nbr of `up' [%d] = [%d]\n",
				pos->pos_act[count_line] + pos->pos_promt[count_line], pos->co_max);
		while ((pos->pos_len[count_line] + pos->pos_promt[count_line]) == pos->co_max)
		{
			tputs(tgetstr("up", NULL), 0, f_putchar);
			count_line++;
		}
		tputs(tgetstr("cr", NULL), 0, f_putchar);
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
		if (history->buf[history->pos_buf][x] == 9)
			tputs(tgetstr("bt", NULL), 0, f_putchar);
		else
			tputs(tgetstr("le", NULL), 0, f_putchar);
		tputs(tgetstr("dc", NULL), 0, f_putchar);
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
		tputs(tgetstr("dc", NULL), 0, f_putchar);
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

int				creat_struct_pos(t_pos *pos)
{
	pos->co_max = tgetnum("co") - 1;
	pos->li_max = tgetnum("li");
	pos->len_tab = tgetnum ("it");
	if ((pos->pos_act = ft_memalloc(sizeof(int) * pos->li_max + 1)) == NULL)
		return (1);
	if ((pos->pos_buf = ft_memalloc(sizeof(int) * pos->li_max + 1)) == NULL)
		return (1);
	if ((pos->pos_len = ft_memalloc(sizeof(int) * pos->li_max + 1)) == NULL)
		return (1);
	if ((pos->pos_promt = ft_memalloc(sizeof(int) * pos->li_max + 1)) == NULL)
		return (1);
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
	if (creat_struct_pos(&pos) == 1)
		return (1);
	fprintf(stderr, "stdin = [%d], stdout = [%d], stderr = [%d]\n", STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO);
	fprintf(stderr, "flag am = [%d]\n", tgetflag("am"));
	fprintf(stderr, "flag xn = [%d]\n", tgetflag("xn"));
	fprintf(stderr, "flag LP = [%d]\n", tgetflag("LP"));
	fprintf(stderr, "flag ns = [%d]\n", tgetflag("ns"));
	fprintf(stderr, "nbr lm = [%d]\n", tgetnum("lm"));
//	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\v\n");
	write(1, PROMT, LEN_PROMT);
//	char *test;
	//test = tgetstr ("ta", NULL);
//	if (test != NULL)
//	{
//		printf("[%d], [%d], [%d], [%d], [%d], [%d], [%d], [%d], [%d]\n",
//		test[0], test[1], test[2], test[3], test[4], test[5], test[6],
//		test[7], test[8]);
//	}
	while (1)
	{
		ft_memset(&buffer, 0, sizeof(char) * 4);
		ret = read(0, buffer, 4095);
//		int		print = 0;
//		printf("ret = [%d]\n", ret);
//		while (print < ret)
//		{
//			printf("[%d]", buffer[print]);
//			print++;
//		}
//		printf("\n");
//		write(1, buffer, ret);
		if (g_sig == SIGINT)
		{
			g_sig = 0;
			return (3);
		}
		if (buffer[0] == 4 && buffer[1] == 0 && buffer[2] == 0)
		{
			return (2);
		}
		if (buffer[0] == 27) // ESC
		{
			if (buffer[1] == 68) //  IND
			{
			}
			else if (buffer[1] == 69) // NEL
			{
			}
			else if (buffer[1] == 72) // HTS
			{
			}
			else if (buffer[1] == 77) // RI
			{
			}
			else if (buffer[1] == 78) // SS2
			{
			}
			else if (buffer[1] == 79) // SS3
			{
			}
			else if (buffer[1] == 80) // DCS
			{
			}
			else if (buffer[1] == 86) // SPA
			{
			}
			else if (buffer[1] == 87) // EPA
			{
			}
			else if (buffer[1] == 88) // SOS
			{
			}
			else if (buffer[1] == 90) // DECID
			{
			}
			else if (buffer[1] == 91) // CSI
			{
			}
			else if (buffer[1] == 92) // ST
			{
			}
			else if (buffer[1] == 93) // OSC
			{
			}
			else if (buffer[1] == 94) // PM
			{
			}
			else if (buffer[1] == 95) // APC
			{
			}
		}
		if (buffer[0] == 127 && buffer[1] == 0 && buffer[2] == 0)
		{
			backspace_key(history);
		}
		else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 51)
		{
			delete_key(history);
		}
		else if (buffer[0] == 27 && buffer[1] == 91)
		{
			if (buffer[2] == 65 && history->pos_buf > 0) // up
			{
				replace_cursor(type, history, &pos, 1);
				history->pos_buf--;
				tputs(tgetstr("cd", NULL), 0, f_putchar);
				write(1, PROMT, LEN_PROMT);
				write(1, history->buf[history->pos_buf],
						history->len[history->pos_buf]);
				history->pos[history->pos_buf] = history->len[history->pos_buf];
				replace_cursor(type, history, &pos, 2);
				replace_cursor(type, history, &pos, 0);
			}
			else if (buffer[2] == 66 && history->pos_buf <
					history->len_buf) // down
			{
				replace_cursor(type, history, &pos, 1);
				history->pos_buf++;
				tputs(tgetstr("cd", NULL), 0, f_putchar);
				write(1, PROMT, LEN_PROMT);
				write(1, history->buf[history->pos_buf],
						history->len[history->pos_buf]);
				history->pos[history->pos_buf] = history->len[history->pos_buf];
				replace_cursor(type, history, &pos, 2);
				replace_cursor(type, history, &pos, 0);
			}
			else if (buffer[2] == 67 && real_length(&pos, real_length(&pos, 0, PROMT, LEN_PROMT),
				history->buf[history->pos_buf],
				history->pos[history->pos_buf]) < real_length(&pos, real_length(&pos, 0, PROMT, LEN_PROMT),
				history->buf[history->pos_buf],
				history->len[history->pos_buf])) // right
			{
				replace_cursor(type, history, &pos, 1);
				history->pos[history->pos_buf]++;
				replace_cursor(type, history, &pos, 0);
			}
			else if (buffer[2] == 68 && real_length(&pos, real_length(&pos, 0, PROMT, LEN_PROMT),
				history->buf[history->pos_buf],
				history->pos[history->pos_buf]) > 0) // left
			{
				replace_cursor(type, history, &pos, 1);
				history->pos[history->pos_buf]--;
				replace_cursor(type, history, &pos, 0);
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
			creat_buf(history, buffer);
			history->pos[history->pos_buf]++;
//			write(STDOUT_FILENO, PROMT, LEN_PROMT);
//			write(STDOUT_FILENO, history->buf[history->pos_buf],
//					history->len[history->pos_buf]);
			int x=0;
			int	len_use = 0;
			while (x < pos.li_max)
			{
				pos.pos_buf[x] = 0;
				x++;
			}
			x = 0;
			add_the_pos_buf(&pos, 0, PROMT, LEN_PROMT);
			fprintf(stderr, "write	PROMT	len_buf = [%d], pos_buf = [%d]\n", history->len[history->pos_buf], history->pos[history->pos_buf]);
			while (pos.pos_buf[x] != 0)
			{
				fprintf(stderr, "write	PROMT	pos.pos_buf[%d] = [%d], pos_buf + 1 = [%d]\n", x, pos.pos_buf[x], (x == 0 ? 0 : pos.pos_buf[x - 1]));
				write(STDOUT_FILENO, PROMT + len_use, pos.pos_buf[x]);
				len_use += pos.pos_buf[x];
				if (pos.pos_buf[x + 1] != 0)
					tputs(tgetstr("do", NULL), 0, f_putchar);
				x++;
			}
			len_use = 0;
			x = 0;
			while (x < pos.li_max)
			{
				pos.pos_buf[x] = 0;
				x++;
			}
			x = 0;
			add_the_pos_buf(&pos, real_length(&pos, 0, PROMT, LEN_PROMT),
					history->buf[history->pos_buf],
					history->len[history->pos_buf]);
			fprintf(stderr, "write	buf	len_buf = [%d], pos_buf = [%d]\n", history->len[history->pos_buf], history->pos[history->pos_buf]);
			while (pos.pos_buf[x] != 0)
			{
				fprintf(stderr, "write	PROMT	pos.pos_buf[%d] = [%d], pos_buf + 1 = [%d]\n", x, pos.pos_buf[x], (x == 0 ? 0 : pos.pos_buf[x - 1]));
				write(STDOUT_FILENO, history->buf[history->pos_buf] + len_use,
						pos.pos_buf[x]);
				len_use += pos.pos_buf[x];
				if (pos.pos_buf[x + 1] != 0)
					tputs(tgetstr("do", NULL), 0, f_putchar);
				x++;
			}
			replace_cursor(type, history, &pos, 2);
			replace_cursor(type, history, &pos, 0);
		}
	}
//	tputs(tgetstr("ei", NULL), 1, f_putchar);
	if (reset_termcaps() == 1)
		return (1);
	return (0);
}
