/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_cmd_fontion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 14:41:40 by gsotty            #+#    #+#             */
/*   Updated: 2017/07/20 14:45:07 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./vingt_et_un_sh.h"

static int		len_of_nbr_ligne(struct winsize win, int len)
{
	int		nbr_ligne_f;
	int		tmp_len;

	tmp_len = (len + 1);
	nbr_ligne_f = -1;
	while (tmp_len > 0)
	{
		if (nbr_ligne_f == -1)
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
		int len)
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

void			new_safe_place(int len)
{
	struct winsize	win;
	int				x;
	int				nbr_ligne_f;

	x = 0;
	ioctl(0, TIOCGWINSZ, &win);
	nbr_ligne_f = len_of_nbr_ligne(win, len);
	if (verif_creat_ligne(win, nbr_ligne_f, len) == 0)
	{
		if (nbr_ligne_f > 0)
		{
			tputs(tgetstr("rc", NULL), 0, f_putchar);
			while (x < nbr_ligne_f)
			{
				tputs(tgetstr("do", NULL), 0, f_putchar);
				x++;
			}
			tputs(tgoto(tgetstr("UP", NULL), 0, nbr_ligne_f), 0, f_putchar);
			tputs(tgoto(tgetstr("RI", NULL), 0, 3), 0, f_putchar);
			tputs(tgetstr("sc", NULL), 0, f_putchar);
		}
	}
}
