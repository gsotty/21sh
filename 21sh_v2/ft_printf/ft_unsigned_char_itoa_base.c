/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_char_itoa_base.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 15:38:12 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/21 15:38:14 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_intlen_base(unsigned char n, int base)
{
	size_t	i;

	i = 1;
	while (n /= base)
		i++;
	return (i);
}

static char		ft_findchar(unsigned char value, int base)
{
	if (value % base < 10)
		return ('0' + (value % base));
	else
		return ('a' - 10 + (value % base));
}

char			*ft_unsigned_char_itoa_base(unsigned char value, int base)
{
	unsigned char	size;
	unsigned char	i;
	char			*tmp;
	unsigned char	u_value;

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
