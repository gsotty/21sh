/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_termcaps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:10:49 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/18 15:18:48 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_termcaps.h"

static void		ft_change_var_term(void)
{
	struct termios	term;

	if (tcgetattr(0, &term) == -1)
		return ;
	term.c_lflag |= (ICANON | ECHO);
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return ;
}

int				ft_reset_termcaps(t_sequence *sequence)
{
	tputs(sequence->end, 0, f_putchar);
	ft_change_var_term();
	free(sequence->start_buf);
	return (0);
}
