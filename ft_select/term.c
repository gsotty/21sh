/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 16:04:41 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/20 12:25:05 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_select.h"

int		reset_term(void)
{
	struct termios	term;
	char			*name_term;

	tputs(tgetstr("te", NULL), 0, f_putchar);
	tputs(tgetstr("ve", NULL), 0, f_putchar);
	tputs(tgetstr("cl", NULL), 0, f_putchar);
	if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, name_term) == ERR)
		return (-1);
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag |= (ICANON | ECHO);
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	return (0);
}

int		prepare_term(void)
{
	struct termios	term;
	char			*name_term;

	if ((name_term = getenv("TERM")) == NULL)
	{
		write(2, "ft_select: TERM not set\n", 24);
		return (-1);
	}
	if (tgetent(NULL, name_term) == ERR)
		return (-1);
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	tputs(tgetstr("ti", NULL), 0, f_putchar);
	tputs(tgetstr("vi", NULL), 0, f_putchar);
	tputs(tgetstr("cl", NULL), 0, f_putchar);
	return (0);
}
