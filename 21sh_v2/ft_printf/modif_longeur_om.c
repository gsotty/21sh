/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_longeur_om.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 16:38:01 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/21 16:38:02 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*modif_longeur_2(t_struc *struc, va_list ap)
{
	uintmax_t	tmp;

	if (struc->lenght.z == 1)
	{
		tmp = (size_t)va_arg(ap, uintmax_t);
		if (tmp == 0)
			struc->flag.nbr_zero = 1;
		return (ft_unsigned_long_itoa_base(tmp, 8));
	}
	else
	{
		tmp = va_arg(ap, unsigned long);
		if (tmp == 0)
			struc->flag.nbr_zero = 1;
		return (ft_unsigned_long_itoa_base(tmp, 8));
	}
}

static char	*modif_longeur_1(t_struc *struc, va_list ap)
{
	uintmax_t	tmp;

	if (struc->lenght.l == 1)
	{
		tmp = (unsigned long)va_arg(ap, uintmax_t);
		if (tmp == 0)
			struc->flag.nbr_zero = 1;
		return (ft_unsigned_long_itoa_base(tmp, 8));
	}
	else if (struc->lenght.ll == 1)
	{
		tmp = va_arg(ap, uintmax_t);
		if (tmp == 0)
			struc->flag.nbr_zero = 1;
		return (ft_uintmax_t_itoa_base(tmp, 8));
	}
	else if (struc->lenght.j == 1)
	{
		tmp = va_arg(ap, uintmax_t);
		if (tmp == 0)
			struc->flag.nbr_zero = 1;
		return (ft_uintmax_t_itoa_base(tmp, 8));
	}
	return (modif_longeur_2(struc, ap));
}

char		*modif_longeur_om(t_struc *struc, va_list ap)
{
	uintmax_t	tmp;

	if (struc->lenght.h == 1)
	{
		tmp = (unsigned short)va_arg(ap, int);
		if (tmp == 0)
			struc->flag.nbr_zero = 1;
		return (ft_itoa_base(tmp, 8));
	}
	else if (struc->lenght.hh == 1)
	{
		tmp = (unsigned short)va_arg(ap, int);
		if (tmp == 0)
			struc->flag.nbr_zero = 1;
		return (ft_itoa_base(tmp, 8));
	}
	return (modif_longeur_1(struc, ap));
}
