/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:28:54 by gsotty            #+#    #+#             */
/*   Updated: 2019/04/04 14:51:12 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/history.h"

int		export_history(t_history *history, int error)
{
	int		fd;
	int		x;

	x = 0;
	if ((fd = open(PATH_HIST, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
		return (1);
	while (x <= history->len)
	{
		if (!(error == 1 && x == history->pos_buf))
		{
			write(fd, history->buf[x]->c, history->buf[x]->len);
			write(fd, "\n", 1);
		}
		free(history->buf[x]->c);
		free(history->buf[x]->type);
		free(history->buf[x]);
		x++;
	}
	free(history->buf);
	free(history->pos);
	close(fd);
	return (0);
}
