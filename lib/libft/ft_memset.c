/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 12:01:30 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/15 15:47:46 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			x;
	unsigned char	*tab;

	tab = (unsigned char *)s;
	x = 0;
	while (x < n)
	{
		tab[x] = (unsigned char)c;
		x++;
	}
	return (s);
}
