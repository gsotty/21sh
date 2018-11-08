/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 08:38:03 by gsotty            #+#    #+#             */
/*   Updated: 2016/11/10 12:09:35 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t		x;
	const char	*tabsrc;
	char		*tabdest;

	x = 0;
	tabsrc = src;
	tabdest = dest;
	while (x < n)
	{
		tabdest[x] = tabsrc[x];
		if (tabsrc[x] == c)
			return (dest + x + 1);
		x++;
	}
	return (NULL);
}
