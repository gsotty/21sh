/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remalloc_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 08:58:11 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/17 09:07:00 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./vingt_et_un_sh.h"

int		remalloc_history(t_history *history)
{
	char	**tmp;
	int		x;

	if (history->len >= history->len_malloc)
	{
		x = 0;
		if ((tmp = ft_memalloc(sizeof(char *) * history->len)) == NULL)
			return (1);
		while (x < history->len)
		{
			tmp[x] = ft_strdup(history->history[x]);
			free(history->history[x]);
			x++;
		}
		free(history->history);
		history->len_malloc += LEN_REMALLOC;
		x = 0;
		if ((history->history = ft_memalloc(sizeof(char *) *
						history->len_malloc)) == NULL)
			return (1);
		while (x < history->len)
		{
			history->history[x] = ft_strdup(tmp[x]);
			free(tmp[x]);
			x++;
		}
		free(tmp);
	}
	return (0);
}
