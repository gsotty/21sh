/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 10:53:29 by gsotty            #+#    #+#             */
/*   Updated: 2017/07/11 16:24:00 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

/*
** **************************************************************************
*/

void	print_tab(char **tableau, int len_tab)
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

char	*creat_buf(char *buffer)
{
	char			*cmd;
	char			*tmp;
	struct winsize	win;
	t_len_cmd		len;
	t_pos			pos;

	ft_memset(&len, 0, sizeof(len));
	ft_memset(&pos, 0, sizeof(pos));
	if ((cmd = ft_memalloc(sizeof(char *) * len.len_cmd_malloc)) == NULL)
		return (NULL);
	ft_memset(buffer, 0, 4);
	write(0, "$> ", 3);
	tputs(tgetstr("sc", NULL), 0, f_putchar);
	while (!(buffer[0] == 10 && buffer[1] == 0 && buffer[2] == 0))
	{
		ioctl(0, TIOCGWINSZ, &win);
		ft_memset(buffer, 0, 4);
		read(0, buffer, 3);
		cmd = remalloc_cmd(&len, cmd);
		if (buffer[0] == 4 && buffer[1] == 0 && buffer[2] == 0)
			return (NULL);
		else if (ft_cursor_move(buffer, &pos, win, len.len) == 0)
			ft_write_cmd(buffer, cmd, &pos, &len);
		//ft_printf("\"%s\"%d, %d, %d\n", buffer, buffer[0], buffer[1], buffer[2]);
	}
	write(0, "\n", 1);
	write(0, cmd, len.len);
	write(0, "\n", 1);
	free(cmd);
	return (buffer);
}

int		main(int argc, char **argv, char **envp)
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
