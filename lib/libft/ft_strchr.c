/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:21:49 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/13 15:29:58 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	x;
	size_t	len;

	x = 0;
	len = ft_strlen(s);
	while (x <= len)
	{
		if (s[x] == c)
		{
			return ((char *)s + x);
		}
		x++;
	}
	return (NULL);
}
