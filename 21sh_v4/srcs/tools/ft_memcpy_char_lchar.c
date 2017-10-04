/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy_char_lchar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 16:55:31 by gsotty            #+#    #+#             */
/*   Updated: 2017/10/04 17:04:41 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

char				*ft_memcpy_char_lchar(char *dest, const t_lchar *src,
		size_t n)
{
	size_t			x;
	size_t			y;
	const t_lchar	*tabsrc;
	char			*tabdest;

	x = 0;
	y = 0;
	tabsrc = src;
	tabdest = dest;
	while (x < n)
	{
		if (tabsrc[x].c != '\0' && tabsrc[x].type != 0)
		{
			tabdest[y] = tabsrc[x].c;
			y++;
		}
		x++;
	}
	tabdest[y] = '\0';
	return (tabdest);
}
