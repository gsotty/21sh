/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_bar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 16:07:40 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/20 12:12:35 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_select.h"

void	return_bar(t_buf *buf)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	g_sig = 0;
	reset_term();
	while (x <= buf->argc)
	{
		if (buf->nbr[x] == 1)
		{
			write(1, buf->tab_arg[x], ft_strlen(buf->tab_arg[x]));
			write(1, " ", 1);
			y = 1;
		}
		x++;
	}
	if (y == 1)
		write(1, "\n", 1);
	free_buf(buf);
	exit(0);
}
