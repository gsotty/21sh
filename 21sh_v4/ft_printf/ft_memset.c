/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 15:34:04 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/21 15:34:06 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;
	char			*ptr;

	i = 0;
	ptr = s;
	while (i < n)
	{
		*(ptr + i) = c;
		i++;
	}
	return (s);
}