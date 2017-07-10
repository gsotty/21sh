/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_m.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 15:32:49 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/21 15:32:52 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static size_t	ft_intlen_base(unsigned int n, int base)
{
	size_t	i;

	i = 1;
	while (n /= base)
		i++;
	return (i);
}

static char		ft_findchar(int value, int base)
{
	if (value % base < 10)
		return ('0' + (value % base));
	else
		return ('A' - 10 + (value % base));
}

char			*ft_itoa_base_m(int value, int base)
{
	size_t			size;
	size_t			i;
	char			*tmp;
	unsigned int	u_value;

	u_value = value < 0 ? -value : value;
	size = (value < 0 && base == 10) ? ft_intlen_base(u_value, base) + 1 :
		ft_intlen_base(u_value, base);
	if (!(tmp = (char*)malloc(sizeof(char) * size + 1)))
		return (NULL);
	tmp[size] = '\0';
	if (!u_value)
		tmp[0] = '0';
	i = size - 1;
	while (u_value)
	{
		tmp[i] = ft_findchar(u_value, base);
		u_value = u_value / base;
		i--;
	}
	if (value < 0 && base == 10)
		tmp[0] = '-';
	return (tmp);
}
