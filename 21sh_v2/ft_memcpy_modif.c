/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy_modif.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 12:25:33 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/21 13:46:03 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./vingt_et_un_sh.h"

void	*ft_memcpy_modif(void *dest, const void *src, size_t n)
{
	size_t				x;
	size_t				y;
	const unsigned char	*tabsrc;
	unsigned char		*tabdest;

	x = 0;
	y = 0;
	tabsrc = src;
	tabdest = dest;
	while (x < n)
	{
		if (tabsrc[x] != '\0')
		{
			tabdest[y] = tabsrc[x];
			y++;
		}
		x++;
	}
	return (tabdest);
}
