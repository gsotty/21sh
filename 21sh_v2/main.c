/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 10:53:29 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/17 16:32:32 by gsotty           ###   ########.fr       */
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

static char		*ft_while_end_of_line(char *buffer,
		t_len_cmd *len, t_pos *pos, t_history history, char **tmp)
{
	struct winsize	win;
	int				len_history;

	ft_memset(&win, 0, sizeof(win));
	ioctl(0, TIOCGWINSZ, &win);
	ft_memset(buffer, 0, sizeof(*buffer) * 4);
	read(0, buffer, 3);
	if ((tmp[pos->history] = remalloc_cmd(len,
					tmp[pos->history])) == NULL)
		return (NULL);
	if (buffer[0] == 4 && buffer[1] == 0 && buffer[2] == 0)
	{
		if (len->len == 0)
		{
			write(0, "exit\n", 5);
			free(tmp[pos->history]);
			return (NULL);
		}
		else
			ft_delete_character_2(tmp[pos->history], len, pos);
	}
	else if (buffer[0] == 12 && buffer[1] == 0 && buffer[2] == 0)
		clear_win(tmp[pos->history], len, pos);
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 51)
		del_muti_line(buffer, tmp[pos->history], pos, len);
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 72)
		ft_key_home(tmp[pos->history], pos, len);
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 70)
		ft_key_end(tmp[pos->history], pos, len);
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 65) // bas
	{
		if (pos->history > 0)
		{
			pos->history -= 1;
			len_history = ft_strlen(tmp[pos->history]);
			pos->pos = len_history;
			pos->nbr_line = len_of_nbr_ligne(win, pos->pos);
			len->len = len_history;
			len->len_cmd_malloc = len_history;
			new_safe_place(len->len);
			write_new_cmd(tmp[pos->history], pos, len_history);
		}
	}
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 66) // haut
	{
		if ((pos->history) < history.len)
		{
			pos->history += 1;
			len_history = ft_strlen(tmp[pos->history]);
			pos->pos = len_history;
			pos->nbr_line = len_of_nbr_ligne(win, pos->pos);
			len->len = len_history;
			len->len_cmd_malloc = len_history;
			new_safe_place(len->len);
			write_new_cmd(tmp[pos->history], pos, len_history);
		}
	}
	else if (buffer[0] == 127 && buffer[1] == 0 && buffer[2] == 0)
		ft_delete_character(tmp[pos->history], len, pos);
	else if (ft_cursor_move(buffer, pos, win, len->len) == 0)
		ft_write_cmd(buffer, tmp[pos->history], pos, len);
	return (tmp[pos->history]);
}

static char		*creat_buf(char *buffer, t_history history)
{
	t_len_cmd		len;
	t_pos			pos;
	char			**tmp;
	char			*cmd;

	tmp = creat_cpy_his(&history);
	tmp[history.len] = NULL;
	ft_signal();
	if ((tmp[history.len] = ini_ligne(&len, &pos,
					tmp[history.len], buffer)) == NULL)
		return (NULL);
	pos.history = history.len;
	while (!(buffer[0] == 10 && buffer[1] == 0 && buffer[2] == 0))
	{
		if ((tmp[pos.history] = ft_while_end_of_line(buffer,
						&len, &pos, history, tmp)) == NULL)
		{
			free_tab(tmp, history.len);
			return (NULL);
		}
		if (g_sig == SIGINT)
		{
			len.len = 0;
			tmp[pos.history][0] = '\0';
			break ;
		}
	}
	write(0, "\n", 1);
	tmp[pos.history][len.len] = '\0';
	cmd = ft_strdup(tmp[pos.history]);
	free_tab(tmp, history.len);
	return (cmd);
}

int				main(int argc, char **argv, char **envp)
{
	t_struc_envp			struc_envp;
	t_history				history;
	char					buffer[4];
	char					*cmd;

	(void)argc;
	(void)argv;
	ft_memset(&struc_envp, 0, sizeof(struc_envp));
	ft_memset(&history, 0, sizeof(history));
	struc_envp.len = len_tab(envp);
	if ((struc_envp.envp = creat_envp(envp, struc_envp.len)) == NULL)
		return (1);
	if ((history.history = creat_history(&history)) == NULL)
		return (1);
	while (1)
	{
		if (prepare_term() != 0)
			break ;
		if ((cmd = creat_buf(buffer, history)) == NULL)
			break ;
		if (add_history(&history, cmd, ft_strlen(cmd)) == 1)
			break ;
		if (reset_term() != 0)
			break ;
		if (parser(cmd, &struc_envp) == 1)
			break ;
	}
	export_history(&history);
	free_tab(struc_envp.envp, struc_envp.len);
	if (reset_term() != 0)
		return (1);
	return (0);
}
