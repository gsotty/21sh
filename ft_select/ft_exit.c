/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 15:08:23 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/20 12:42:49 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_select.h"

void	ft_exit(int x, t_buf *buf, char *err)
{
	g_sig = 0;
	reset_term();
	if (x == 2 && err != NULL)
	{
		write(2, err, ft_strlen(err));
		free_buf(buf);
		exit(-1);
	}
	free_buf(buf);
	exit(x);
}
