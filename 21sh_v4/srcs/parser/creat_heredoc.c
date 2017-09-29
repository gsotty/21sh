/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 16:00:41 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/29 16:30:44 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

/*
**	ft_printf("\n[%d], [%d], [%d]\n", buffer[0], buffer[1], buffer[2]);
*/

static t_lchar	*ft_while_end_of_line(char *buffer, t_pos *pos,
		t_history *history)
{
	ft_memset(buffer, 0, sizeof(*buffer) * 4);
	read(0, buffer, 3);
	if ((history->history[pos->history] = remalloc_cmd_lchar(pos,
					history->history[pos->history])) == NULL)
		return (NULL);
	if (key_of_keyboard_heredoc(buffer, pos, history) == 1)
		return (NULL);
	return (history->history[pos->history]);
}

static int		new_line_buf(t_history *history, int *nbr_line, int x,
		t_line **line)
{
	if (x >= *nbr_line)
	{
		if ((*line = remalloc_line(*line, history, *nbr_line,
						*nbr_line + LEN_REMAL_LI)) == NULL)
			return (1);
		*nbr_line += LEN_REMAL_LI;
	}
	write(1, _PROMPT_ML, _PROMPT_LEN_WRITE_ML);
	tputs(tgetstr("sc", NULL), 0, f_putchar);
	return (0);
}

static t_line	*init_creat_buf(t_history *history)
{
	int			x;
	t_line		*line;

	x = 0;
	if ((line = ft_memalloc(sizeof(t_line) * LEN_REMAL_LI)) == NULL)
		return (NULL);
	while (x < LEN_REMAL_LI)
	{
		if ((line[x].pos = ft_memalloc(sizeof(t_pos))) == NULL)
			return (NULL);
		if ((line[x].history = creat_cpy_history(history)) == NULL)
			return (NULL);
		line[x].pos->history = line[x].history->len;
		x = x + 1;
	}
	write(0, _PROMPT_ML, _PROMPT_LEN_WRITE_ML);
	tputs(tgetstr("sc", NULL), 0, f_putchar);
	return (line);
}

t_lchar			*creat_heredoc(char *eof, int nbr_line, char *buffer,
		t_history *history)
{
	int			x;
	t_line		*line;

	x = 0;
	if ((line = init_creat_buf(history)) == NULL)
		return (NULL);
	while (1)
	{
		if (!(ft_while_end_of_line(buffer, line[x].pos, line[x].history)))
			return (free_struct_line(line, nbr_line));
		if (buffer[0] == 10 && buffer[1] == 0 && buffer[2] == 0)
		{
			if (ft_strcmp(convert_lchar_to_char(line[x].history->history
							[line[x].pos->history]), ft_strjoin(eof, "\n")) == 0)
				break ;
			if (new_line_buf(history, &nbr_line, ++x, &line) == 1)
				return (NULL);
		}
	}
	return (end_of_creat_buf_heredoc(line, x, nbr_line));
}
