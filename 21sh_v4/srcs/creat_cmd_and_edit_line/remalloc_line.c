/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remalloc_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 15:36:08 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/20 15:37:55 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

t_line	*remalloc_line(t_line *line, t_history *history, int len, int new_len)
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
