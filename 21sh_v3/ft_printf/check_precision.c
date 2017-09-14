/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 15:28:44 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/28 10:44:23 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_precision(t_struc *struc, int z, int y, va_list ap)
{
	while (y < z)
	{
		if (struc->str[y] == '.')
		{
			if (struc->str[y + 1] == '*')
				struc->precision.number = va_arg(ap, int);
			else
				struc->precision.number = ft_atoi((char *)struc->str + y + 1);
			return (1);
		}
		y++;
	}
	struc->precision.number = -1;
	return (0);
}
