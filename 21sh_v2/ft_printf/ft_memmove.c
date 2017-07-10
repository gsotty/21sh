/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 15:33:50 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/21 15:33:52 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = n - 1;
	if (src < dest)
		while ((int)j >= 0)
		{
			((char*)dest)[j] = ((char*)src)[j];
			j--;
		}
	else
		while (i < n)
		{
			((char*)dest)[i] = ((char*)src)[i];
			i++;
		}
	return (dest);
}
