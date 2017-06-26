/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 15:54:36 by gsotty            #+#    #+#             */
/*   Updated: 2016/11/10 15:45:50 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	x;
	size_t	len;

	x = 0;
	while (dest[x] && x < n)
		x++;
	len = x;
	while (src[x - len] && x < n - 1)
	{
		dest[x] = src[x - len];
		x++;
	}
	if (len < n)
		dest[x] = '\0';
	return (len + ft_strlen(src));
}
