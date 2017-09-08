/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remalloc_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 08:58:11 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/08 11:49:43 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static int	remalloc_history_2(int x, char **tmp, t_history *history)
{
	if ((tmp = ft_memalloc(sizeof(char *) * (history->len + 2))) == NULL)
		return (1);
	while (x < history->len)
	{
		tmp[x] = ft_strdup(history->history[x]);
		free(history->history[x]);
		x++;
	}
	tmp[x] = NULL;
	free(history->history);
	history->len_malloc += LEN_REMALLOC;
	x = 0;
	if ((history->history = ft_memalloc(sizeof(char *) *
					(history->len_malloc + 2))) == NULL)
		return (1);
	while (x < history->len)
	{
		history->history[x] = ft_strdup(tmp[x]);
		free(tmp[x]);
		x++;
	}
	history->history[x] = NULL;
	free(tmp);
	return (0);
}

int			remalloc_history(t_history *history)
{
	if (history->len >= history->len_malloc)
	{
		if (remalloc_history_2(0, NULL, history) == 1)
			return (1);
	}
	return (0);
}
