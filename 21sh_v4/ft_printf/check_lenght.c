/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lenght.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 15:28:18 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/28 10:39:46 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_lenght_1(t_struc *struc, const char *str, int y)
{
	if (str[y] == 'l')
	{
		struc->lenght.l = 1;
		return (1);
	}
	if (str[y] == 'j')
	{
		struc->lenght.j = 1;
		return (1);
	}
	if (str[y] == 'z')
	{
		struc->lenght.z = 1;
		return (1);
	}
	return (0);
}

int			check_lenght(t_struc *struc, int z, int y)
{
	while (y < z)
	{
		if (struc->str[y] == 'h' && struc->str[y + 1] == 'h')
		{
			struc->lenght.hh = 1;
			return (1);
		}
		if (struc->str[y] == 'h')
		{
			struc->lenght.h = 1;
			return (1);
		}
		if (struc->str[y] == 'l' && struc->str[y + 1] == 'l')
		{
			struc->lenght.ll = 1;
			return (1);
		}
		if ((check_lenght_1(struc, struc->str, y)) != 0)
			return (1);
		y++;
	}
	return (0);
}
