/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ft_select.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 15:55:40 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/20 13:01:41 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_select.h"

static void		ft_signal(void)
{
	struct sigaction	act;

	ft_memset(&act, '\0', sizeof(act));
	act.sa_sigaction = &signal_tstp;
	act.sa_flags = SA_SIGINFO | SA_NODEFER;
	sigaction(SIGTSTP, &act, NULL);
	ft_memset(&act, '\0', sizeof(act));
	act.sa_sigaction = &signal_cont;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGCONT, &act, NULL);
	ft_memset(&act, '\0', sizeof(act));
	act.sa_sigaction = &signal_int;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGILL, &act, NULL);
	sigaction(SIGABRT, &act, NULL);
	sigaction(SIGFPE, &act, NULL);
	sigaction(SIGSEGV, &act, NULL);
	sigaction(SIGTERM, &act, NULL);
	sigaction(SIGPIPE, &act, NULL);
	sigaction(SIGALRM, &act, NULL);
	sigaction(SIGWINCH, &act, NULL);
}

static void		ft_sigwinch(void)
{
	g_sig = 0;
	ioctl(0, TIOCSTI, "");
}

static int		verif_sig(t_buf *buf)
{
	if (g_sig == SIGINT)
		ft_exit(2, buf, "ft_select: signal: SIGINT\n");
	if (g_sig == SIGQUIT)
		ft_exit(2, buf, "ft_select: signal: SIGQUIT\n");
	if (g_sig == SIGILL)
		ft_exit(2, buf, "ft_select: signal: SIGILL\n");
	if (g_sig == SIGABRT)
		ft_exit(2, buf, "ft_select: signal: SIGABRT\n");
	if (g_sig == SIGFPE)
		ft_exit(2, buf, "ft_select: signal: SIGFPE\n");
	if (g_sig == SIGSEGV)
		ft_exit(2, buf, "ft_select: signal: SIGSEGV\n");
	if (g_sig == SIGTERM)
		ft_exit(2, buf, "ft_select: signal: SIGTERM\n");
	if (g_sig == SIGPIPE)
		ft_exit(2, buf, "ft_select: signal: SIGPIPE\n");
	if (g_sig == SIGALRM)
		ft_exit(2, buf, "ft_select: signal: SIGALARM\n");
	return (0);
}

void			read_ft_select(t_buf *buf)
{
	char				buffer[3];

	ft_signal();
	if (buf->argc == 0)
		ft_exit(2, buf, "ft_select: no argument\n");
	ft_print_argv(buf);
	if (g_sig == SIGWINCH)
		ft_sigwinch();
	ft_memset(buffer, 0, 3);
	read(0, buffer, 3);
	if (((buffer[0] == 3 || buffer[0] == 4 || buffer[0] == 26 ||
					buffer[0] == 27) && buffer[1] == 0 && buffer[2] == 0) ||
			verif_sig(buf) == 1)
		ft_exit(1, buf, NULL);
	else if (buffer[0] == 27)
		fleche_directionnelle(buffer, buf);
	else if (buffer[0] == 1 && buffer[1] == 0 && buffer[2] == 0)
		all_select(buf);
	else if (buffer[0] == 32 && buffer[1] == 0 && buffer[2] == 0)
		space_bar(buf);
	else if (buffer[0] == 10 && buffer[1] == 0 && buffer[2] == 0)
		return_bar(buf);
	else if ((buffer[0] == 127 || buffer[0] == 126) && buffer[1] == 0 &&
			buffer[2] == 0)
		delete_bar(buf);
}
