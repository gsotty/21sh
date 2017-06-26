/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 08:10:35 by gsotty            #+#    #+#             */
/*   Updated: 2016/12/16 13:12:24 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				x;
	const unsigned char	*tabsrc;
	unsigned char		*tabdest;

	x = 0;
	tabsrc = src;
	tabdest = dest;
	while (x < n)
	{
		tabdest[x] = tabsrc[x];
		x++;
	}
	return (tabdest);
}
