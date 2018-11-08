/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy_lchar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 09:08:44 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/19 12:00:29 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

t_lchar		*ft_memcpy_lchar(t_lchar *dest, const t_lchar *src, size_t n)
{
	size_t				x;
	size_t				y;
	const t_lchar		*tabsrc;
	t_lchar				*tabdest;

	x = 0;
	y = 0;
	tabsrc = src;
	tabdest = dest;
	while (x < n)
	{
		if (tabsrc[x].c != '\0')
		{
			tabdest[y].c = tabsrc[x].c;
			tabdest[y].type = tabsrc[x].type;
			y++;
		}
		x++;
	}
	tabdest[y].c = '\0';
	tabdest[y].type = 0;
	return (tabdest);
}
