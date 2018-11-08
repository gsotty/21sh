/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 15:02:35 by gsotty            #+#    #+#             */
/*   Updated: 2016/11/11 09:59:20 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t		x;
	size_t		len;

	x = 0;
	len = ft_strlen((char *)src);
	while (x < n)
	{
		if (x > len)
			dest[x] = '\0';
		else
			dest[x] = src[x];
		x++;
	}
	return (dest);
}
