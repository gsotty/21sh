/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freehistory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:29:19 by gsotty            #+#    #+#             */
/*   Updated: 2019/04/04 14:29:21 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vingt_et_un_sh.h"
#include "../../include/lchar.h"

int				ft_freehistory(t_history *history)
{
	int		count;

	count = 0;
	while (count < history->malloc)
	{
		free(history->buf[count]->c);
		free(history->buf[count]->type);
		free(history->buf[count]);
		count++;
	}
	free(history->pos);
	free(history->buf);
	return (0);
}
