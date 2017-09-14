/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 09:23:16 by gsotty            #+#    #+#             */
/*   Updated: 2016/11/12 11:10:03 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int				x;
	unsigned char	y;
	unsigned char	*tab;

	x = 0;
	y = (unsigned char)c;
	tab = (unsigned char *)s;
	while (n--)
	{
		if (tab[x] == y)
		{
			return (tab + x);
		}
		x++;
	}
	return (NULL);
}
