/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintmax_t_itoa_base_m.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 15:37:57 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/21 15:37:59 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_intlen_base(uintmax_t n, int base)
{
	long	i;

	i = 1;
	while (n /= base)
		i++;
	return (i);
}

static char		ft_findchar(uintmax_t value, int base)
{
	if (value % base < 10)
		return ('0' + (value % base));
	else
		return ('A' - 10 + (value % base));
}

char			*ft_uintmax_t_itoa_base_m(uintmax_t value, int base)
{
	uintmax_t	size;
	uintmax_t	i;
	char		*tmp;
	uintmax_t	u_value;

	u_value = value;
	size = ft_intlen_base(u_value, base);
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
	return (tmp);
}
