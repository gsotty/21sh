/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 09:21:54 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/18 15:50:49 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int		export_history(t_history *history)
{
	int		fd;
	int		x;
	int		y;
	int		len;

	x = 0;
	if ((fd = open(PATH_HISTORY, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
		return (1);
	while (x < history->len)
	{
		y = 0;
		len = ft_strlen_lchar(history->history[x]);
		while (y < len)
		{
			write(fd, &history->history[x][y].c, 1);
			y++;
		}
		write(fd, "\n", 1);
		free(history->history[x]);
		x++;
	}
	free(history->history);
	return (0);
}
