/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 16:00:41 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/27 16:20:43 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

/*
**	ft_printf("\n[%d], [%d], [%d]\n", buffer[0], buffer[1], buffer[2]);
*/

static t_lchar	*ft_while_end_of_line(char *buffer, t_pos *pos,
		t_history *history, int modif_prompt)
{
	ft_memset(buffer, 0, sizeof(*buffer) * 4);
	read(0, buffer, 3);
	if ((history->history[pos->history] = remalloc_cmd_lchar(pos,
					history->history[pos->history])) == NULL)
		return (NULL);
	if (key_of_keyboard(buffer, pos, history, modif_prompt) == 1)
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

static t_line	*init_creat_buf(t_history *history, t_quote *quote)
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
	ft_memset(quote, 0, sizeof(t_quote));
	write(0, _PROMPT, _PROMPT_LEN_WRITE);
	tputs(tgetstr("sc", NULL), 0, f_putchar);
	return (line);
}

static int		ctrl_c(t_line *line, int x)
{
	if (g_sig == SIGINT)
	{
		g_sig = 0;
		line[x].pos->len = 0;
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}

t_lchar			*creat_buf(int x, int nbr_line, char *buffer,
		t_history *history)
{
	t_quote		quote;
	t_line		*line;

	if ((line = init_creat_buf(history, &quote)) == NULL)
		return (NULL);
	while (1)
	{
		loop_creat_buf(x, line, &quote);
		if (!(ft_while_end_of_line(buffer, line[x].pos, line[x].history, x)))
			return (free_struct_line(line, nbr_line));
		if (buffer[0] == 10 && buffer[1] == 0 && buffer[2] == 0)
		{
			if (verif_line(&quote, _LINE) == 1)
			{
				if (new_line_buf(history, &nbr_line, ++x, &line) == 1)
					return (NULL);
			}
			else
				break ;
		}
		else if (ctrl_c(line, x) == 1)
			break ;
	}
	return (end_of_creat_buf(line, x, nbr_line));
}
