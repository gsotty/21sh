/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 15:29:44 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/28 10:45:43 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_isnum(int c)
{
	if (('0' <= c && c <= '9'))
		return (1);
	return (0);
}

int			check_width(t_struc *struc, int z, int y, va_list ap)
{
	while (y < z && struc->str[y] != '.')
	{
		if (struc->str[y] == '*')
			struc->width.number = va_arg(ap, int);
		if ((ft_isnum(struc->str[y]) == 1) && struc->str[y] != '0')
		{
			struc->width.number = ft_atoi((char *)struc->str + y);
			return (1);
		}
		y++;
	}
	return (0);
}
