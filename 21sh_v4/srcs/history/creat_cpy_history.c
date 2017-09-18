/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_cpy_his.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 14:54:56 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/18 16:35:26 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

t_history	*creat_cpy_history(t_history *history)
{
	int			x;
	t_history	*new_history;

	x = 0;
	if ((new_history = ft_memalloc(sizeof(t_history))) == NULL)
		return (NULL);
	new_history->len = history->len;
	new_history->len_malloc = history->len_malloc;
	if ((new_history->history = ft_memalloc(sizeof(t_lchar *) *
					(history->len + 2))) == NULL)
		return (new_history);
	while (x < history->len)
	{
		new_history->history[x] = ft_strdup_lchar(history->history[x]);
		x++;
	}
	new_history->history[x] = NULL;
	return (new_history);
}
