/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vingt_et_un_sh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 11:56:19 by gsotty            #+#    #+#             */
/*   Updated: 2017/06/25 17:16:13 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./vingt_et_un_sh.h"

int		creat_buffer()
{
	return (0);
}

int		while_vingt_et_un_sh(t_pos *pos)
{
	int		x;
	char	buffer[3];
	char	buf[MAX_CANON + 1];

	x = 0;
	write(1, "$> ", 3);
	pos->pos_y++;
	pos->pos_x += 3;
	ft_memset(buffer, 0, 3);
	ft_memset(buf, 0, MAX_CANON);
	while (!(buffer[0] == 10 && buffer[1] == 0 && buffer[2] == 0))
	{
		ft_memset(buffer, 0, 3);
		read(0, buffer, 3);
	//	printf("%d, %d, %d\n", buffer[0], buffer[1], buffer[2]);
		if ((buffer[0] == 27 || buffer[0] == 4) && buffer[1] == 0 &&
			buffer[2] == 0)
			return (1);
		else if (buffer[0] == 5 && buffer[1] == 0 && buffer[2] == 0)
		{
			tputs(tgetstr("sc", NULL), 1 , f_putchar);
		}
		else if (buffer[0] == 23 && buffer[1] == 0 && buffer[2] == 0)
		{
			tputs(tgetstr("rc", NULL), 1 , f_putchar);
		}
		else if (buffer[0] == 127 && buffer[1] == 0 && buffer[2] == 0)
		{
			if (pos->pos_x > 3)
				pos->pos_x--;
			tputs(tgetstr("le", NULL), 1 , f_putchar);
			tputs(tgetstr("dc", NULL), 1 , f_putchar);
			x--;
			buf[pos->pos_x - 3] = ' ';
		}
		else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 'D')
		{
			if (pos->pos_x > 3)
				pos->pos_x--;
			tputs(tgetstr("le", NULL), 1 , f_putchar);
		//	tputs(tgoto(tgetstr("cm", NULL), pos->pos_x, pos->pos_y), 1,
		//			f_putchar);
		}
		else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 'C')
		{
			pos->pos_x++;
			tputs(tgetstr("nd", NULL), 1 , f_putchar);
//			tputs(tgoto(tgetstr("cm", NULL), pos->pos_x, pos->pos_y), 1,
//					f_putchar);
		}
		else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 'B')
		{
			pos->pos_y++;
			tputs(tgetstr("do", NULL), 1 , f_putchar);
			//tputs(tgetstr("sr", NULL), 1 , f_putchar);
			//tputs(tgoto(tgetstr("cm", NULL), pos->pos_x, pos->pos_y), 1,
		///			f_putchar);
		}
		else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 'A')
		{
			pos->pos_y--;
			tputs(tgetstr("up", NULL), 1 , f_putchar);
	//		tputs(tgoto(tgetstr("cm", NULL), pos->pos_x, pos->pos_y), 1,
	//				f_putchar);
		}
		else if (buffer[1] == 0 && buffer[2] == 0 && buffer[0] != 10)
		{
			write(1, buffer, 1);
			buf[pos->pos_x - 3] = buffer[0];
			pos->pos_x++;
		}
	}
	printf("\n%s\n", buf);
	return (0);
}

int		vingt_et_un_sh(char **envp_begin)
{
	t_pos	pos;

	printf("%d\n", MAX_CANON);
	printf("%d\n", MAX_INPUT);
	ft_memset(&pos, 0, sizeof(pos));
	(void)envp_begin;
	if (prepare_term() == -1)
		return (-1);
	while (1)
	{
		pos.pos_x = 0;
		if (while_vingt_et_un_sh(&pos) != 0)
			break ;
	}
	reset_term();
	return (0);
}
