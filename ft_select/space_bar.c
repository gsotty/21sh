/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_bar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 15:52:11 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/12 15:07:55 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_select.h"

void	space_bar(t_buf *buf)
{
	if (buf->nbr[buf->pos] == 0)
		buf->nbr[buf->pos] = 1;
	else
		buf->nbr[buf->pos] = 0;
	if (buf->pos < buf->argc - 1)
		buf->pos++;
	else
		buf->pos = 0;
}
