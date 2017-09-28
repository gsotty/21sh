/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 12:55:20 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/28 14:56:17 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static void		no_end_of_ligne(char buffer, char *cmd, t_pos *pos)
{
	int				x;
	char			tmp_cmd;
	char			tmp_buf;

	x = pos->pos;
	tmp_buf = buffer;
	while (x < (pos->len + 2))
	{
		tmp_cmd = cmd[x];
		cmd[x] = tmp_buf;
		tmp_buf = cmd[x + 1];
		cmd[x + 1] = tmp_cmd;
		x += 2;
	}
}

static void		put_buffer_to_heredoc(char buffer, char *cmd, t_pos *pos)
{
	if (cmd[pos->pos] == '\0')
	{
		cmd[pos->pos] = buffer;
	}
	else
		no_end_of_ligne(buffer, cmd, pos);
}

void			write_new_heredoc(char *cmd, t_pos *pos)
{
	struct winsize	win;
	int				x;

	(void)pos;
	ioctl(0, TIOCGWINSZ, &win);
	tputs(tgetstr("rc", NULL), 0, f_putchar);
	tputs(tgetstr("cr", NULL), 0, f_putchar);
	tputs(tgetstr("cd", NULL), 0, f_putchar);
	write(0, _PROMPT_ML, _PROMPT_LEN_WRITE_ML);
	write(0, cmd, pos->len);
	x = 0;
	while (x < (pos->len - pos->pos))
	{
		tputs(tgetstr("le", NULL), 0, f_putchar);
		x++;
	}
}

void			ft_write_heredoc(char *buffer, char *cmd, t_pos *pos)
{
	int		x;

	x = 0;
	while (x < 3)
	{
		if (buffer[x] == 10)
			pos->pos = pos->len;
		if (ft_isprint(buffer[x]) == 1 || (buffer[x] == 10))
		{
			put_buffer_to_heredoc(buffer[x], cmd, pos);
			pos->pos++;
			pos->len++;
			new_safe_place_heredoc(pos->len, nbr_new_line_heredoc(cmd));
			write_new_heredoc(cmd, pos);
		}
		x++;
	}
}
