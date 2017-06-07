/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 09:07:10 by gsotty            #+#    #+#             */
/*   Updated: 2017/06/07 14:19:35 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vingt_et_un_sh.h"
#include "../includes/tools.h"
#include "../includes/builtin.h"

void	signal_int(int x, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;
	g_sig = x;
}

int		verif_sig(int len, char *buf)
{
	struct sigaction	act;

	ft_memset(&act, '\0', sizeof(act));
	act.sa_sigaction = &signal_int;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGTSTP, &act, NULL);
	sigaction(SIGCONT, &act, NULL);
	if (g_sig == SIGINT || g_sig == SIGTSTP || g_sig == SIGCONT)
	{
		g_sig = 0;
		ft_memset(buf, 0, len);
		len = 0;
		ioctl(0, TIOCSTI, "\n");
		return (0);
	}
	prepare_term();
	return (len);
}

int		vingt_et_un_sh(int argc, char **argv, char ***envp)
{
	int					x;
	int					j;
	int					z;
	int					y;
	int					nbr_line;
	int					len;
	char				tmp;
	char				tmp_2;
	char				buffer[3];
	char				buf[4096];
	struct winsize		win;

	if (prepare_term() == -1)
		return (1);
	len = 0;
	x = 0;
	while (1)
	{
		ft_memset(buf, 0, len + 1);
		nbr_line = 0;
		x = 0;
		len = 0;
		write(1, PRONT, LEN_PRONT);
		ft_memset(buffer, 0, 3);
		while (!(buffer[0] == 10 && buffer[1] == 0 && buffer[2] == 0))
		{
			ioctl(0, TIOCGWINSZ, &win);
			ft_memset(buffer, 0, 3);
			len = verif_sig(len, buf);
			if (len == 0)
				x = 0;
			read(0, buffer, 3);
		//	printf("111 = %d, %d, %d\n", buffer[0], buffer[1], buffer[2]);
			if (buffer[0] == 4 && buffer[1] == 0 && buffer[2] == 0)
			{
				if (len == 0)
				{
					write(1, "exit\n", 5);
					reset_term();
					free_tab(*envp);
					return (0);
				}
				else
				{
					tputs(tgetstr("dc", NULL), 1 , f_putchar);
					y = x;
					while (y < (len + 1))
					{
						buf[y] = buf[y + 1];
						y++;
					}
					buf[y] = '\0';
					len--;
				}
			}
			else if ((buffer[0] == 5 && buffer[1] == 0 && buffer[2] == 0) ||
					(buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 70))
			{
				tputs(tgetstr("ei", NULL), 1 , f_putchar);
				write(1, buf + x, len - x);
				tputs(tgetstr("im", NULL), 1 , f_putchar);
				x = len;
			}
			else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 72)
			{
				z = x;
				while (z > 0)
				{
					tputs(tgetstr("le", NULL), 1 , f_putchar);
					z--;
				}
				x = 0;
			}
			else if (buffer[0] == 12 && buffer[1] == 0 && buffer[2] == 0)
			{
				tputs(tgetstr("cl", NULL), 1 , f_putchar);
				write(1, PRONT, LEN_PRONT);
				write(1, buf, len);
			}
			else if (buffer[0] == 27 && buffer[1] == 0 && buffer[2] == 0)
			{
				ft_memset(buffer, 0, 3);
				read(0, buffer, 3);
				if (len < 4086)
				{
					j = 0;
					while (buffer[j] != '\0')
					{
						if (ft_isprint(buffer[j]) == 1)
						{
							write(1, buffer + j, 1);
							if (buf[x] != '\0')
							{
								y = x;
								tmp_2 = buffer[j];
								while (y < (len + 2))
								{
									tmp = buf[y];
									buf[y] = tmp_2;
									tmp_2 = buf[y + 1];
									buf[y + 1] = tmp;
									y += 2;
								}
								len++;
							}
							else
							{
								buf[x] = buffer[j];
							}
							x++;
						}
						j++;
					}
				}
			}
			else if (buffer[0] == 27 && buffer[1] == 91)
			{
				if (buffer[2] == 65)
				{}
				else if (buffer[2] == 66)
				{}
				else if (buffer[2] == 67)
				{
					if (x < len && len != 0)
					{
						write(1, buffer, 3);
						x++;
					}
				}
				else if (buffer[2] == 68)
				{
					if (x > 0)
					{
						write(1, buffer, 3);
						x--;
					}
				}
				else if (buffer[2] == 51)
				{
					if (x < len)
					{
						tputs(tgetstr("dc", NULL), 1 , f_putchar);
						y = x;
						while (y < (len + 1))
						{
							buf[y] = buf[y + 1];
							y++;
						}
						buf[y] = '\0';
						len--;
					}
					read(0, buffer, 3);
				}
			}
			else if (buffer[0] == 127 && buffer[1] == 0 && buffer[2] == 0)
			{
				if (x > 0)
				{
					tputs(tgetstr("le", NULL), 1 , f_putchar);
					tputs(tgetstr("dc", NULL), 1 , f_putchar);
					y = x - 1;
					while (y < (len + 1))
					{
						buf[y] = buf[y + 1];
						y++;
					}
					buf[y] = '\0';
					len--;
					x--;
				}
			}
			else if (buffer[0] != 10)
			{
				if (len < 4086)
				{
					j = 0;
					while (buffer[j] != '\0')
					{
						if (ft_isprint(buffer[j]) == 1)
						{
							write(1, buffer + j, 1);
							if (buf[x] != '\0')
							{
								y = x;
								tmp_2 = buffer[j];
								while (y < (len + 2))
								{
									tmp = buf[y];
									buf[y] = tmp_2;
									tmp_2 = buf[y + 1];
									buf[y + 1] = tmp;
									y += 2;
								}
								buf[y] = '\0';
								len++;
							}
							else
							{
								buf[x] = buffer[j];
								buf[x + 1] = '\0';
							}
							x++;
						}
						j++;
					}
				}
			}
			if (len < x)
				len = x;
		}
		write(1, "\n", 1);
		if (ft_strcmp(buf, "exit") == 0)
			break ;
		parser(len, buf, envp);
	}
	reset_term();
	free_tab(*envp);
	return (0);
}
