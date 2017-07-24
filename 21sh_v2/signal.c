/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 15:15:00 by gsotty            #+#    #+#             */
/*   Updated: 2017/07/24 10:48:47 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./vingt_et_un_sh.h"

void	signal_act(int x, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;
	g_sig = x;
}

void	ft_signal_child(void)
{
	struct sigaction	act;

	g_sig = 0;
	ft_memset(&act, '\0', sizeof(act));
	act.sa_sigaction = &signal_act;
	act.sa_flags = SA_RESETHAND;
	sigaction(SIGINT, &act, NULL);
}

void	ft_signal(void)
{
	struct sigaction	act;

	g_sig = 0;
	ft_memset(&act, '\0', sizeof(act));
	act.sa_sigaction = &signal_act;
	act.sa_flags = SA_SIGINFO | SA_RESETHAND;
	sigaction(SIGINT, &act, NULL);
}
