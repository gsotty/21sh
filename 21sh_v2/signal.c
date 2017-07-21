/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 15:15:00 by gsotty            #+#    #+#             */
/*   Updated: 2017/07/21 15:46:49 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./vingt_et_un_sh.h"

void	signal_act(int x, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;
	g_sig = x;
}

void	ft_signal(void)
{
	int					x;
	struct sigaction	act;

	x = 0;
	g_sig = 0;
	ft_memset(&act, '\0', sizeof(act));
	act.sa_sigaction = &signal_act;
	act.sa_flags = SA_SIGINFO;
	while (x < 31)
	{
		if (x != SIGKILL && x != SIGSTOP)
			sigaction(x, &act, NULL);
		x++;
	}
}
