/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 09:21:54 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/24 15:47:44 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int		export_history(t_history *history)
{
	int		fd;
	int		x;

	x = 0;
	if ((fd = open(PATH_HISTORY, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
		return (1);
	while (x < history->len)
	{
		write(fd, history->history[x], ft_strlen(history->history[x]));
		write(fd, "\n", 1);
		free(history->history[x]);
		x++;
	}
	free(history->history);
	return (0);
}
