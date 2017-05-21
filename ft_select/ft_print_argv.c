/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 18:05:18 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/19 14:43:30 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include "./ft_select.h"

static void		check_len_win(t_buf *buf)
{
	struct winsize		win;

	ioctl(0, TIOCGWINSZ, &win);
	buf->lig = (win.ws_row - 1);
	buf->col = win.ws_col;
}

static void		ft_while_printf_argv(t_buf *buf, int y, int x, int pos)
{
	int		len;
	int		len_write;

	len = 0;
	len_write = 0;
	tputs(tgoto(tgetstr("cm", NULL), ((buf->max_len + 1) * (y)), x), 1,
			f_putchar);
	len = ft_strlen(buf->tab_arg[pos]);
	len_write = ((buf->max_len + 1) * y) + len;
	while (len_write > buf->col && len > 0)
	{
		len_write = ((buf->max_len + 1) * y) + len;
		len--;
	}
	if (buf->nbr[pos] == 1 &&
			buf->pos == pos)
		print_sur_et_sou(buf, pos, len);
	else if (buf->pos == pos)
		print_sou(buf, pos, len);
	else if (buf->nbr[pos] == 1)
		print_sur(buf, pos, len);
	else
		write(0, buf->tab_arg[pos], len);
}

static void		ft_len_max(t_buf *buf)
{
	int		len;
	int		x;

	x = 0;
	len = 0;
	while (buf->tab_arg[x] != NULL)
	{
		if (buf->max_len < (len = (int)ft_strlen(buf->tab_arg[x])))
			buf->max_len = len;
		x++;
	}
}

int				ft_print_argv(t_buf *buf)
{
	int		x;
	int		j;
	int		y;
	int		z;

	j = 0;
	y = 0;
	x = -1;
	check_len_win(buf);
	ft_len_max(buf);
	buf->max_lig = buf->argc;
	tputs(tgetstr("cl", NULL), 0, f_putchar);
	z = ((buf->pos - (buf->max_lig * (buf->pos / buf->max_lig)))
			/ buf->lig);
	while (++x < buf->lig && buf->tab_arg[j + (buf->lig * z)] != NULL)
	{
		ft_while_printf_argv(buf, y, x, (j + (buf->lig * z)));
		if (x == (buf->lig - 1))
		{
			x = -1;
			y++;
		}
		j++;
	}
	return (0);
}
