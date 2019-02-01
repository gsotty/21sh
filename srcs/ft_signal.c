/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 15:15:00 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/20 11:48:00 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vingt_et_un_sh.h"

static void		signal_act(int x, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;
	g_sig = x;
}

void			ft_signal(int signum, int flags)
{
	struct sigaction	act;

	g_sig = 0;
	ft_memset(&act, '\0', sizeof(act));
	act.sa_sigaction = &signal_act;
	sigemptyset(&act.sa_mask);
	act.sa_flags = flags;
	sigaction(signum, &act, NULL);
}
