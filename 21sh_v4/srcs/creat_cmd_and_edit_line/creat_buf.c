/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 16:00:41 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/18 18:10:01 by gsotty           ###   ########.fr       */
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

int			creat_buf(char *buffer, t_history *history)
{
	int			x;
	t_line		*line;

	x = 0;
	if ((line = ft_memalloc(sizeof(t_line *) * LEN_REMAL_LI)) == NULL)
		return (1);
	while (x < LEN_REMAL_LI)
	{
		if ((line[x].pos = ft_memalloc(sizeof(t_pos))) == NULL)
			return (1);
		if ((line[x].history = creat_cpy_history(history)) == NULL)
			return (1);
		x++;
	}
	return (0);
}
