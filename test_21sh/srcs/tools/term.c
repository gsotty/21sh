/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 16:04:41 by gsotty            #+#    #+#             */
/*   Updated: 2017/06/08 12:32:05 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tools.h"

int		reset_term(void)
{
	struct termios	term;
	char			*name_term;

	tputs(tgetstr("ei", NULL), 0, f_putchar);
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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int		prepare_term(void)
{
	struct termios	term;
	char			*name_term;
	int				x;
	int				fd;
	char			*line;

	if ((name_term = getenv("TERM")) == NULL)
	{
		write(2, "21sh: TERM not set\n", 24);
		return (-1);
	}
	if (tgetent(NULL, name_term) == ERR)
	{
		write(2, "21sh: TERM not set\n", 24);
		return (-1);
	}
	if (tcgetattr(0, &term) == -1)
	{
		write(2, "21sh: TERM not set\n", 24);
		return (-1);
	}
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
	{
		write(2, "21sh: TERM not set\n", 24);
		return (-1);
	}
	tputs(tgetstr("im", NULL), 0, f_putchar);
	return (0);
}