/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 16:00:41 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/19 17:19:10 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

/*
   t_lchar		*cmd;
   t_len_cmd	len;

   ft_memset(&len, 0, sizeof(t_len_cmd));
   if ((cmd = ft_memalloc(sizeof(t_lchar) * LEN_REMALLOC)) == NULL)
   return (1);
   len.len_malloc = LEN_REMALLOC;
   */
/*
   static t_history	**remalloc_cpy_history(t_len_cmd *len,
   t_history **cpy_history, t_history *history)
   {
   int			x;
   t_history	**new_cpy_history;

   x = 0;
   if ((new_cpy_history = ft_memalloc(sizeof(t_history *) * (len->len_malloc +
   LEN_REMAL_LI + 1))) == NULL)
   return (NULL);
   while (x < len->len_malloc)
   {
   new_cpy_history[x] = cpy_history[x];
   }
   len->len_malloc =+ LEN_REMAL_LI;
   while (x < len->len_malloc)
   {
   new_cpy_history[x] = creat_cpy_history(history);
   x++;
   }
   free(cpy_history);
   return (new_cpy_history);
   }
   */

static void		free_struct_line(t_line *line, int nbr_line)
{
	int		x;

	x = 0;
	while (x < nbr_line)
	{
		free(line[x].pos);
		free_tab_lchar(line[x].history->history);
		free(line[x].history);
		x++;
	}
	free(line);
}

/*
   static int		buf_ini(t_len_cmd *len, t_pos *pos, t_history *history,
   char *buffer)
   {
   ft_memset(pos, 0, sizeof(*pos));
   ft_memset(buffer, 0, sizeof(*buffer) * 4);
   if ((history->history[history->len] = ft_memalloc(sizeof(t_lchar *) *
   (len->len_malloc + 2))) == NULL)
   return (1);
   pos->history = history->len;
   write(0, _PROMPT, _PROMPT_LEN_WRITE);
   tputs(tgetstr("sc", NULL), 0, f_putchar);
   return (0);
   }
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

static t_line	*remalloc_line(t_line *line, t_history *history, int len,
		int new_len)
{
	t_line		*new_line;
	int			x;

	x = 0;
	if ((new_line = ft_memalloc(sizeof(t_line) * new_len)) == NULL)
		return (NULL);
	while (x < len)
	{
		new_line[x].pos = line[x].pos;
		new_line[x].history = line[x].history;
		x++;
	}
	while (x < new_len)
	{
		if ((new_line[x].pos = ft_memalloc(sizeof(t_pos))) == NULL)
			return (NULL);
		if ((new_line[x].history = creat_cpy_history(history)) == NULL)
			return (NULL);
		x++;
	}
	free(line);
	return (new_line);
}

t_lchar			*creat_cmd(t_line *line, int nbr_line)
{
	t_lchar		*cmd;
	int			x;
	int			len_cmd;

	x = 0;
	len_cmd = 0;
	while (x <= nbr_line)
	{
		len_cmd += line[x].pos->len;
		x++;
	}
	ft_printf("[%d]\n", len_cmd);
	if ((cmd = ft_memalloc(sizeof(t_lchar) * (len_cmd + 1))) == NULL)
		return (NULL);
	x = 0;
	len_cmd = 0;
	while (x <= nbr_line)
	{
		ft_memcpy_lchar(cmd + len_cmd,
				line[x].history->history[line[x].pos->history],
				line[x].pos->len);
		len_cmd += line[x].pos->len;
		x++;
	}
	int	y=0;
	while (cmd[y].c != '\0')
	{
		write(1, &cmd[y].c, 1);
		y++;
	}
	write(1, "\n", 1);
	return (cmd);
}

int				creat_buf(char *buffer, t_history *history)
{
	int			x;
	int			nbr_line;
	t_quote		quote;
	t_line		*line;

	x = 0;
	if ((line = ft_memalloc(sizeof(t_line) * LEN_REMAL_LI)) == NULL)
		return (1);
	while (x < LEN_REMAL_LI)
	{
		if ((line[x].pos = ft_memalloc(sizeof(t_pos))) == NULL)
			return (1);
		if ((line[x].history = creat_cpy_history(history)) == NULL)
			return (1);
		x++;
	}
	nbr_line = LEN_REMAL_LI;
	x = 0;
	ft_memset(buffer, 0, sizeof(char) * 4);
	if (x == NO_MODIF_PROMPT)
		write(0, _PROMPT, _PROMPT_LEN_WRITE);
	else
		write(0, _PROMPT_ML, _PROMPT_LEN_WRITE_ML);
	tputs(tgetstr("sc", NULL), 0, f_putchar);
	ft_memset(&quote, 0, sizeof(t_quote));
	while (1)
	{
		line[x].pos->is_quote = quote.is_quote;
		line[x].pos->is_dquote = quote.is_dquote;
		if (ft_while_end_of_line(buffer, line[x].pos, line[x].history, x)
				== NULL)
		{
			ft_key_end(line[x].history->history[line[x].pos->history],
					line[x].pos, x);
			free_struct_line(line, nbr_line);
			return (0);
		}
		if (buffer[0] == 10 && buffer[1] == 0 && buffer[2] == 0)
		{
			if (quote.is_quote == 0 && quote.is_dquote == 0)
				break ;
			else
			{
				x++;
				if (x >= nbr_line)
				{
					if ((line = remalloc_line(line, history, nbr_line,
									nbr_line + LEN_REMAL_LI)) == NULL)
						return (1);
					nbr_line += LEN_REMAL_LI;
				}
				if (x == NO_MODIF_PROMPT)
					write(0, _PROMPT, _PROMPT_LEN_WRITE);
				else
					write(0, _PROMPT_ML, _PROMPT_LEN_WRITE_ML);
				tputs(tgetstr("sc", NULL), 0, f_putchar);
			}
		}
		else if (buffer[0] == 34 && buffer[1] == 0 && buffer[2] == 0)
		{
			if (quote.is_dquote == 0 && quote.is_quote == 0)
				quote.is_dquote = 1;
			else if (quote.is_dquote == 1)
				quote.is_dquote = 0;
		}
		else if (buffer[0] == 39 && buffer[1] == 0 && buffer[2] == 0)
		{
			if (quote.is_quote == 0 && quote.is_dquote == 0)
				quote.is_quote = 1;
			else if (quote.is_quote == 1)
				quote.is_quote = 0;
		}
	}
	ft_key_end(line[x].history->history[line[x].pos->history], line[x].pos, x);
	creat_cmd(line, x);
	free_struct_line(line, nbr_line);
	return (0);
}
