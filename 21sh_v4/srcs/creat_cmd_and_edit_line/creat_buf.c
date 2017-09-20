/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 16:00:41 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/20 18:02:06 by gsotty           ###   ########.fr       */
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
/*
static int		quote_and_dquote(char *buffer, t_quote *quote)
{
	quote->is_backslash = 0;
	if (buffer[0] == 34 && buffer[1] == 0 && buffer[2] == 0)
	{
		if (quote->is_dquote == 0 && quote->is_quote == 0)
			quote->is_dquote = 1;
		else if (quote->is_dquote == 1)
			quote->is_dquote = 0;
	}
	else if (buffer[0] == 39 && buffer[1] == 0 && buffer[2] == 0)
	{
		if (quote->is_quote == 0 && quote->is_dquote == 0)
			quote->is_quote = 1;
		else if (quote->is_quote == 1)
			quote->is_quote = 0;
	}
	else if (buffer[0] == 92 && buffer[1] == 0 && buffer[2] == 0)
		quote->is_backslash = 1;
	return (0);
}
*/
static int		verif_line(t_quote *quote, t_lchar *cmd)
{
	int		x;

	x = 0;
	while (cmd[x].c != '\0')
	{
		if (quote->is_quote == 0 && quote->is_dquote == 0 &&
				quote->is_backslash == 0 && cmd[x].c == '\'')
			quote->is_quote = 1;
		else if (quote->is_quote == 1 && quote->is_dquote == 0 &&
				quote->is_backslash == 0 && cmd[x].c == '\'')
			quote->is_quote = 0;
		else if (quote->is_dquote == 0 && quote->is_quote == 0 &&
				quote->is_backslash == 0 && cmd[x].c == '\"')
			quote->is_dquote = 1;
		else if (quote->is_dquote == 1 && quote->is_quote == 0 &&
				quote->is_backslash == 0 && cmd[x].c == '\"')
			quote->is_dquote = 0;
		else if (cmd[x + 1].c != '\0')
		{
			if (cmd[x].c == '\\')
				x++;
		}
		/*
		else if (quote->is_backslash == 0 && quote->is_quote == 0 &&
				quote->is_dquote == 0 && cmd[x].c == '\\' && cmd[x + 1].c == '\0')
			quote->is_backslash = 1;
		else if (quote->is_backslash == 1 && quote->is_quote == 0 &&
				quote->is_dquote == 0 && cmd[x].c == '\\' && cmd[])
			quote->is_backslash = 0;
		*/
		x++;
	}
	if (quote->is_quote == 1 || quote->is_dquote == 1 ||
			quote->is_backslash == 1)
		return (1);
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
		x = x + 1;
	}
	ft_memset(quote, 0, sizeof(t_quote));
	write(0, _PROMPT, _PROMPT_LEN_WRITE);
	tputs(tgetstr("sc", NULL), 0, f_putchar);
	return (line);
}

int				creat_buf(int x, int nbr_line, char *buffer, t_history *history)
{
	t_quote		quote;
	t_line		*line;

	if ((line = init_creat_buf(history, &quote)) == NULL)
		return (1);
	while (1)
	{
		line[x].pos->is_quote = quote.is_quote;
		line[x].pos->is_dquote = quote.is_dquote;
		line[x].pos->is_backslash = quote.is_backslash;
		if (!(ft_while_end_of_line(buffer, line[x].pos, line[x].history, x)))
			return (free_struct_line(line, nbr_line));
		if (buffer[0] == 10 && buffer[1] == 0 && buffer[2] == 0)
		{
			if (verif_line(&quote,
						line[x].history->history[line[x].pos->history]) == 1)
			{
				x++;
				if (new_line_buf(history, &nbr_line, x, &line) == 1)
					return (1);
			}
			else
				break ;
		/*	if (quote.is_quote == 0 && quote.is_dquote == 0 &&
					quote.is_backslash == 0)
				break ;
			if (new_line_buf(history, &nbr_line, &x, &line) == 1)
				return (1);
*/		}
		else if (g_sig == SIGINT)
		{
			line[x].pos->len = 0;
			write(1, "\n", 1);
			break ;
		}
	}
	end_of_creat_buf(line, x, nbr_line);
	return (0);
}
