/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 09:01:21 by gsotty            #+#    #+#             */
/*   Updated: 2016/11/13 11:03:59 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		x;
	char		*tabdest;
	const char	*tabsrc;

	x = 0;
	tabdest = dest;
	tabsrc = src;
	if (dest <= src || src >= (dest + n))
	{
		while (x < n)
		{
			tabdest[x] = tabsrc[x];
			x++;
		}
	}
	else
	{
		while (n)
		{
			tabdest[n - 1] = tabsrc[n - 1];
			n--;
		}
	}
	return (dest);
}
