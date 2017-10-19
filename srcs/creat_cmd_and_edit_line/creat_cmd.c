/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 15:38:49 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/29 15:47:38 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static t_lchar		*creat_cmd(int x, t_line *line, int nbr_line)
{
	t_lchar		*cmd;
	int			len_cmd;

	len_cmd = 0;
	while (x <= nbr_line)
	{
		len_cmd += line[x].pos->len;
		x++;
	}
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
	if (len_cmd > 0)
		cmd[len_cmd - 1].c = '\0';
	return (cmd);
}

t_lchar				*end_of_creat_buf(t_line *line, int x, int nbr_line)
{
	t_lchar		*cmd;

	if (line[x].pos->len > 0)
		ft_key_end(line[x].history->history[line[x].pos->history],
				line[x].pos, x);
	cmd = creat_cmd(0, line, x);
	free_struct_line(line, nbr_line);
	return (cmd);
}
