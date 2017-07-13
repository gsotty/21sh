/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 10:53:29 by gsotty            #+#    #+#             */
/*   Updated: 2017/07/13 15:52:21 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

/*
** **************************************************************************
*/

void			print_tab(char **tableau, int len_tab)
{
	int		x;

	x = 0;
	while (x < len_tab)
	{
		write(0, tableau[x], ft_strlen(tableau[x]));
		write(0, "\n", 1);
		x++;
	}
}

/*
** **************************************************************************
*/

static char		*ini_ligne(t_len_cmd *len, t_pos *pos, char *cmd, char *buffer)
{
	ft_memset(len, 0, sizeof(*len));
	ft_memset(pos, 0, sizeof(*pos));
	if ((cmd = ft_memalloc(sizeof(char *) * len->len_cmd_malloc)) == NULL)
		return (NULL);
	ft_memset(buffer, 0, 4);
	write(0, "$> ", 3);
	tputs(tgetstr("sc", NULL), 0, f_putchar);
	return (cmd);
}

static char		*ft_while_end_of_line(char *buffer, char *cmd,
		t_len_cmd *len, t_pos *pos)
{
	struct winsize	win;

	ft_memset(&win, 0, sizeof(win));
	ioctl(0, TIOCGWINSZ, &win);
	ft_memset(buffer, 0, 4);
	read(0, buffer, 3);
	if ((cmd = remalloc_cmd(len, cmd)) == NULL)
		return (NULL);
	if (buffer[0] == 4 && buffer[1] == 0 && buffer[2] == 0)
		return (NULL);
	else if (buffer[0] == 12 && buffer[1] == 0 && buffer[2] == 0)
		clear_win(cmd, len, pos, win);
	else if (ft_cursor_move(buffer, pos, win, len->len) == 0)
		ft_write_cmd(buffer, cmd, pos, len);
	return (cmd);
}

char			*creat_buf(char *buffer)
{
	char			*cmd;
	char			*tmp;
	t_len_cmd		len;
	t_pos			pos;

	if ((cmd = ini_ligne(&len, &pos, cmd, buffer)) == NULL)
		return (NULL);
	while (!(buffer[0] == 10 && buffer[1] == 0 && buffer[2] == 0))
	{
		if ((cmd = ft_while_end_of_line(buffer, cmd, &len, &pos)) == NULL)
			return (NULL);
	}
	write(0, "\n", 1);
	write(0, cmd, len.len);
	write(0, "\n", 1);
	free(cmd);
	return (buffer);
}

int				main(int argc, char **argv, char **envp)
{
	int		len_envp;
	char	**tab_envp;
	char	buffer[4];

	len_envp = len_tab(envp);
	if ((tab_envp = creat_envp(envp, len_envp)) == NULL)
		return (1);
	while (1)
	{
		if (prepare_term() != 0)
			break ;
		if (creat_buf(buffer) == NULL)
			break ;
	}
	free_tab(tab_envp, len_envp);
	if (reset_term() != 0)
		return (1);
	return (0);
}
