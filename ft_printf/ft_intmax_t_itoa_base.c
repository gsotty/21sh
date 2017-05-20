/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intmax_t_itoa_base.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 15:30:53 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/21 15:31:03 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static intmax_t	ft_intlen_base(intmax_t n, int base)
{
	intmax_t	i;

	i = 1;
	while (n /= base)
		i++;
	return (i);
}

static char		ft_findchar(intmax_t value, int base)
{
	if (value % base < 10)
		return ('0' + (value % base));
	else
		return ('a' - 10 + (value % base));
}

char			*ft_intmax_t_itoa_base(intmax_t value, int base)
{
	intmax_t	size;
	intmax_t	i;
	char		*tmp;
	intmax_t	u_value;

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
