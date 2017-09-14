/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 09:07:55 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/14 15:53:29 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

/*
** ft_printf("[%d], [%d], [%d]\n", buffer[0], buffer[1], buffer[2]);
*/

static int			buf_ini(t_len_cmd *len, t_pos *pos, t_history *history,
		char *buffer)
{
	ft_memset(pos, 0, sizeof(*pos));
	ft_memset(buffer, 0, sizeof(*buffer) * 4);
	if ((history->history[history->len] = ft_memalloc(sizeof(t_lchar *) *
					(len->len_cmd_malloc + 2))) == NULL)
		return (1);
	pos->history = history->len;
	write(0, _PROMPT, _PROMPT_LEN_WRITE);
	tputs(tgetstr("sc", NULL), 0, f_putchar);
	return (0);
}

static t_lchar			*ft_while_end_of_line(char *buffer,
		t_len_cmd *len, t_pos *pos, t_history *history)
{
	ft_memset(buffer, 0, sizeof(*buffer) * 4);
	read(0, buffer, 3);
	if ((history->history[pos->history] = remalloc_cmd_lchar(len,
					history->history[pos->history])) == NULL)
		return (NULL);
	if (key_of_keyboard(buffer, len, pos, history) == 1)
		return (NULL);
	return (history->history[pos->history]);
}

static int			verif_quote_and_heredoc(char *buffer, t_len_cmd *len,
		t_pos *pos, t_history *history)
{
	int		x;
	int		is_quote;
	int		is_dquote;

	(void)len;
	(void)buffer;
	x = 0;
	is_quote = 0;
	is_dquote = 0;
	while (history->history[pos->history][x].c != '\0')
	{
		if (history->history[pos->history][x].c == '\'')
		{
			if (is_quote == 0)
				is_quote = 1;
			else if (is_quote == 1)
				is_quote = 0;
		}
		else if (history->history[pos->history][x].c == '\'')
		{
			if (is_dquote == 0)
				is_dquote = 1;
			else if (is_dquote == 1)
				is_dquote = 0;
		}
		x++;
	}
	return (0);
}

static t_lchar		*buf_loop(char *buffer, t_history history, t_lchar *cmd,
		t_len_cmd *len)
{
	t_pos			pos;
	int				is_quote;
	int				is_dquote;

	is_quote = 0;
	is_dquote = 0;
	if (buf_ini(len, &pos, &history, buffer) == 1)
		return (NULL);
	while (1)
	{
	//	ft_printf("[%d], [%d], [%d]\n", buffer[0], buffer[1], buffer[2]);
		if (ft_while_end_of_line(buffer, len, &pos, &history) == NULL)
		{
			free_tab_lchar(history.history, history.len);
			return (NULL);
		}
		if (buffer[0] == 10 && buffer[1] == 0 && buffer[2] == 0)
		{
			if (pos.is_quote == 0 && pos.is_dquote == 0)
				break ;
		}
		else if (buffer[0] == 34 && buffer[1] == 0 && buffer[2] == 0)
		{
			if (pos.is_dquote == 0 && pos.is_quote == 0)
				pos.is_dquote = 1;
			else if (pos.is_dquote == 1)
				pos.is_dquote = 0;
		}
		else if (buffer[0] == 39 && buffer[1] == 0 && buffer[2] == 0)
		{
			if (pos.is_quote == 0 && pos.is_dquote == 0)
				pos.is_quote = 1;
			else if (pos.is_quote == 1)
				pos.is_quote = 0;
		}
		else if (buffer[0] == 92 && buffer[1] == 0 && buffer[2] == 0)
		{
			
		}
		else if (g_sig == SIGINT)
		{
			len->len = 0;
			break ;
		}
	}
	write(0, "\n", 1);
	verif_quote_and_heredoc(buffer, len, &pos, &history);
	if ((cmd = ft_memalloc(sizeof(t_lchar) * (len->len + 1))) == NULL)
		return (NULL);
	ft_memcpy_lchar(cmd, history.history[pos.history], len->len);
	cmd[len->len].c = '\0';
	free_tab_lchar(history.history, history.len);
	return (cmd);
}

t_lchar				*creat_buf(char *buffer, t_len_cmd *len,
		t_history *history)
{
	t_lchar			*cmd;

	ft_signal();
	if ((cmd = buf_loop(buffer, creat_cpy_history(history), NULL,
					len)) == NULL)
		return (NULL);
	if (add_history(history, cmd, len->len) == 1)
		return (NULL);
	return (cmd);
}
