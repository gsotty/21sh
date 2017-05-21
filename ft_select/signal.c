/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 16:00:52 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/20 12:36:37 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_select.h"

void	signal_int(int x, siginfo_t *siginfo, void *context)
{
	if (siginfo)
	{
	}
	if (context)
	{
	}
	g_sig = x;
}

void	signal_tstp(int x, siginfo_t *siginfo, void *context)
{
	if (siginfo)
	{
	}
	if (context)
	{
	}
	reset_term();
	signal(x, SIG_DFL);
	ioctl(0, TIOCSTI, "\032");
}

void	signal_cont(int x, siginfo_t *siginfo, void *context)
{
	if (x)
	{
	}
	if (siginfo)
	{
	}
	if (context)
	{
	}
	prepare_term();
	ioctl(0, TIOCSTI, "");
	tputs(tgetstr("vi", NULL), 0, f_putchar);
	tputs(tgetstr("cl", NULL), 0, f_putchar);
}
