/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 14:47:57 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/21 12:01:49 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static void		no_end_of_ligne(char buffer, t_lchar *cmd, t_pos *pos)
{
	int				x;
	t_lchar			tmp_cmd;
	char			tmp_buf;

	x = pos->pos;
	tmp_buf = buffer;
	while (x < (pos->len + 2))
	{
		tmp_cmd.c = cmd[x].c;
		tmp_cmd.type = cmd[x].type;
		cmd[x].c = tmp_buf;
		if (cmd[x].c == 10)
			cmd[x].type = _NEW_LINE;
		else
			cmd[x].type = _WORD;
		tmp_buf = cmd[x + 1].c;
		cmd[x + 1].c = tmp_cmd.c;
		cmd[x + 1].type = tmp_cmd.type;
		x += 2;
	}
}

static void		put_buffer_to_cmd(char buffer, t_lchar *cmd, t_pos *pos)
{
	if (cmd[pos->pos].c == '\0')
	{
		cmd[pos->pos].c = buffer;
		if (cmd[pos->pos].c == 10)
			cmd[pos->pos].type = _NEW_LINE;
		else
			cmd[pos->pos].type = _WORD;
	}
	else
		no_end_of_ligne(buffer, cmd, pos);
}

void			write_new_cmd(t_lchar *cmd, t_pos *pos, int modif_prompt)
{
	struct winsize	win;
	int				x;

	(void)pos;
	ioctl(0, TIOCGWINSZ, &win);
	tputs(tgetstr("rc", NULL), 0, f_putchar);
	tputs(tgetstr("cr", NULL), 0, f_putchar);
	tputs(tgetstr("cd", NULL), 0, f_putchar);
	if (modif_prompt == NO_MODIF_PROMPT)
		write(0, _PROMPT, _PROMPT_LEN_WRITE);
	else
		write(0, _PROMPT_ML, _PROMPT_LEN_WRITE_ML);
	x = 0;
	while (x < pos->len)
	{
		write(0, &cmd[x].c, 1);
		x++;
	}
	x = 0;
	while (x < (pos->len - pos->pos))
	{
		tputs(tgetstr("le", NULL), 0, f_putchar);
		x++;
	}
}

void			ft_write_cmd(char *buffer, t_lchar *cmd, t_pos *pos,
		int modif_prompt)
{
	int		x;

	x = 0;
	while (x < 3)
	{
		if (buffer[x] == 10)
			pos->pos = pos->len;
		if (ft_isprint(buffer[x]) == 1 || (buffer[x] == 10))
		{
			put_buffer_to_cmd(buffer[x], cmd, pos);
			pos->pos++;
			pos->len++;
			new_safe_place(pos->len, nbr_new_line(cmd), modif_prompt);
			write_new_cmd(cmd, pos, modif_prompt);
		}
		x++;
	}
}
