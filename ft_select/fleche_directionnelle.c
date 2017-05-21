/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fleche_directionnelle.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:22:44 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/18 15:02:30 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	fleche_directionnelle(char *buffer, t_buf *buf)
{
	if (buffer[1] == 91)
	{
		if (buffer[2] == 'A')
		{
			if (buf->pos > 0)
				buf->pos--;
			else
				buf->pos = buf->argc - 1;
		}
		if (buffer[2] == 'B')
		{
			if (buf->pos < buf->argc - 1)
				buf->pos++;
			else
				buf->pos = 0;
		}
		if (buffer[2] == 'C')
			if (buf->pos < (buf->argc - buf->lig))
				buf->pos = buf->pos + buf->lig;
		if (buffer[2] == 'D')
			if (buf->pos >= buf->lig)
				buf->pos = buf->pos - buf->lig;
	}
}
