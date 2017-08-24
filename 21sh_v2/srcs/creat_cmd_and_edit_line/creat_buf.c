/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 09:07:55 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/24 15:42:26 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

/*
** ft_printf("%d, %d, %d\n", buffer[0], buffer[1], buffer[2]);
*/

static int			buf_ini(t_len_cmd *len, t_pos *pos, t_history *history,
		char *buffer)
{
	ft_memset(pos, 0, sizeof(*pos));
	ft_memset(buffer, 0, sizeof(*buffer) * 4);
	if ((history->history[history->len] = ft_memalloc(sizeof(char *) *
					(len->len_cmd_malloc + 2))) == NULL)
		return (1);
	pos->history = history->len;
	write(0, "$> ", 3);
	tputs(tgetstr("sc", NULL), 0, f_putchar);
	return (0);
}

static char			*ft_while_end_of_line(char *buffer,
		t_len_cmd *len, t_pos *pos, t_history *history)
{
	ft_memset(buffer, 0, sizeof(*buffer) * 4);
	read(0, buffer, 3);
	if ((history->history[pos->history] = remalloc_cmd(len,
					history->history[pos->history])) == NULL)
		return (NULL);
	if (key_of_keyboard(buffer, len, pos, history) == 1)
		return (NULL);
	return (history->history[pos->history]);
}

static char			*buf_loop(char *buffer, t_history history, char *cmd,
		t_len_cmd *len)
{
	t_pos			pos;

	if (buf_ini(len, &pos, &history, buffer) == 1)
		return (NULL);
	while (!(buffer[0] == 10 && buffer[1] == 0 && buffer[2] == 0))
	{
		if (ft_while_end_of_line(buffer, len, &pos, &history) == NULL)
		{
			free_tab(history.history, history.len);
			return (NULL);
		}
		if (g_sig == SIGINT)
		{
			len->len = 0;
			break ;
		}
	}
	write(0, "\n", 1);
	if ((cmd = ft_memalloc(sizeof(char) * (len->len + 1))) == NULL)
		return (NULL);
	ft_memcpy(cmd, history.history[pos.history], len->len);
	cmd[len->len] = '\0';
	free_tab(history.history, history.len);
	return (cmd);
}

char				*creat_buf(char *buffer, t_len_cmd *len,
		t_history *history)
{
	char			*cmd;

	ft_signal();
	if ((cmd = buf_loop(buffer, creat_cpy_history(history), NULL,
					len)) == NULL)
		return (NULL);
	if (add_history(history, cmd, len->len) == 1)
		return (NULL);
	return (cmd);
}
