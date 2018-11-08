/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 11:26:20 by gsotty            #+#    #+#             */
/*   Updated: 2016/11/12 12:02:06 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

char	*ft_strcat(char *dest, const char *src)
{
	int	x;
	int	len;

	x = 0;
	len = ft_strlen(dest);
	while (src[x] != '\0')
	{
		dest[len + x] = src[x];
		x++;
	}
	dest[len + x] = '\0';
	return (dest);
}
