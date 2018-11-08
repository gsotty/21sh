/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 10:24:09 by gsotty            #+#    #+#             */
/*   Updated: 2016/11/12 13:28:51 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*tabs1;
	unsigned char	*tabs2;

	tabs1 = (void *)s1;
	tabs2 = (void *)s2;
	while (n && (*tabs1 == *tabs2))
	{
		tabs1++;
		tabs2++;
		n--;
	}
	if (!n)
		return (0);
	return (*tabs1 - *tabs2);
}
