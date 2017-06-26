/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 11:43:42 by gsotty            #+#    #+#             */
/*   Updated: 2016/11/12 13:32:35 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	len;
	size_t	x;

	x = 0;
	len = ft_strlen(dest);
	while (src[x] != '\0' && x < n)
	{
		dest[len + x] = src[x];
		x++;
	}
	dest[len + x] = '\0';
	return (dest);
}
