/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 10:53:29 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/09 17:05:00 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

/*
** **************************************************************************
** ft_printf("%d, %d, %d\n", buffer[0], buffer[1], buffer[2]);
*/

static char		*ini_ligne(t_len_cmd *len, t_pos *pos, char *cmd, char *buffer)
{
	ft_memset(len, 0, sizeof(*len));
	ft_memset(pos, 0, sizeof(*pos));
	if ((cmd = ft_memalloc(sizeof(char *) * (len->len_cmd_malloc + 1))) == NULL)
		return (NULL);
	ft_memset(buffer, 0, sizeof(*buffer) * 4);
	write(0, "$> ", 3);
	tputs(tgetstr("sc", NULL), 0, f_putchar);
	return (cmd);
}

static void		del_muti_line(char *buffer, char *cmd, t_pos *pos,
		t_len_cmd *len)
{
	ft_memset(buffer, 0, sizeof(*buffer) * 4);
	read(0, buffer, 3);
	if (buffer[0] == 126 && buffer[1] == 0 && buffer[2] == 0)
		ft_delete_character_2(cmd, len, pos);
}

static char		*ft_while_end_of_line(char *buffer, char *cmd,
		t_len_cmd *len, t_pos *pos)
{
	struct winsize	win;

	ft_memset(&win, 0, sizeof(win));
	ioctl(0, TIOCGWINSZ, &win);
	ft_memset(buffer, 0, sizeof(*buffer) * 4);
	read(0, buffer, 3);
	if ((cmd = remalloc_cmd(len, cmd)) == NULL)
		return (NULL);
	if (buffer[0] == 4 && buffer[1] == 0 && buffer[2] == 0)
	{
		if (len->len == 0)
		{
			write(0, "exit\n", 5);
			return (NULL);
		}
		else
			ft_delete_character_2(cmd, len, pos);
	}
	else if (buffer[0] == 12 && buffer[1] == 0 && buffer[2] == 0)
		clear_win(cmd, len, pos);
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 51)
		del_muti_line(buffer, cmd, pos, len);
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 72)
		ft_key_home(cmd, pos, len);
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 70)
		ft_key_end(cmd, pos, len);
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 65)
	{
		historique(2, &cmd, len);
		pos->nbr_line = len_of_nbr_ligne(win, pos->pos);
		new_safe_place(len->len);
		write_new_cmd(cmd, pos, len->len);
	}
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 66)
	{
		historique(3, &cmd, len);
		pos->nbr_line = len_of_nbr_ligne(win, pos->pos);
		new_safe_place(len->len);
		write_new_cmd(cmd, pos, len->len);
	}
	else if (buffer[0] == 127 && buffer[1] == 0 && buffer[2] == 0)
		ft_delete_character(cmd, len, pos);
	else if (ft_cursor_move(buffer, pos, win, len->len) == 0)
		ft_write_cmd(buffer, cmd, pos, len);
	return (cmd);
}

static char		*creat_buf(char *buffer)
{
	char			*cmd;
	t_len_cmd		len;
	t_pos			pos;

	cmd = NULL;
	ft_signal();
	if ((cmd = ini_ligne(&len, &pos, cmd, buffer)) == NULL)
		return (NULL);
	while (!(buffer[0] == 10 && buffer[1] == 0 && buffer[2] == 0))
	{
		if ((cmd = ft_while_end_of_line(buffer, cmd, &len, &pos)) == NULL)
			return (NULL);
		if (g_sig == SIGINT)
		{
			len.len = 0;
			cmd[0] = '\0';
			break ;
		}
	}
	write(0, "\n", 1);
	cmd[len.len] = '\0';
	historique(1, &cmd, &len);
	return (cmd);
}

int				main(int argc, char **argv, char **envp)
{
	t_struc_envp			struc_envp;
	char					buffer[4];
	char					*cmd;

	(void)argc;
	(void)argv;
	ft_memset(&struc_envp, 0, sizeof(struc_envp));
	struc_envp.len = len_tab(envp);
	if ((struc_envp.envp = creat_envp(envp, struc_envp.len)) == NULL)
		return (1);
	while (1)
	{
		if (prepare_term() != 0)
			break ;
		if ((cmd = creat_buf(buffer)) == NULL)
			break ;
		if (reset_term() != 0)
			break ;
		if (parser(cmd, &struc_envp) == 1)
			break ;
	}
	free_tab(struc_envp.envp, struc_envp.len);
	if (reset_term() != 0)
		return (1);
	return (0);
}
