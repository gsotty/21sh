/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_longeur_d_and_i.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 15:41:04 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/21 15:41:05 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*modif_longeur_3(t_struc *struc, va_list ap, intmax_t tmp)
{
	if (struc->lenght.z == 1)
	{
		tmp = va_arg(ap, size_t);
		if (tmp < 0)
		{
			struc->flag.negatif = 1;
			tmp = -tmp;
		}
		if (tmp == 0)
			struc->flag.nbr_zero = 1;
		return (ft_uintmax_t_itoa_base((size_t)tmp, 10));
	}
	else
	{
		tmp = va_arg(ap, int);
		if (tmp < 0)
		{
			struc->flag.negatif = 1;
			tmp = -tmp;
		}
		if (tmp == 0)
			struc->flag.nbr_zero = 1;
		return (ft_uintmax_t_itoa_base((size_t)tmp, 10));
	}
}

static char	*modif_longeur_2(t_struc *struc, va_list ap, intmax_t tmp)
{
	if (struc->lenght.l == 1)
	{
		tmp = va_arg(ap, long);
		if (tmp < 0)
		{
			struc->flag.negatif = 1;
			tmp = -tmp;
		}
		if (tmp == 0)
			struc->flag.nbr_zero = 1;
		return (ft_unsigned_long_itoa_base((long)tmp, 10));
	}
	else if (struc->lenght.hh == 1)
	{
		tmp = (char)va_arg(ap, int);
		if (tmp < 0)
		{
			struc->flag.negatif = 1;
			tmp = -tmp;
		}
		if (tmp == 0)
			struc->flag.nbr_zero = 1;
		return (ft_itoa(tmp));
	}
	return (modif_longeur_3(struc, ap, 0));
}

static char	*modif_longeur_1(t_struc *struc, va_list ap, intmax_t tmp)
{
	if (struc->lenght.ll == 1)
	{
		tmp = va_arg(ap, long long);
		if (tmp < 0)
		{
			struc->flag.negatif = 1;
			tmp = -tmp;
		}
		if (tmp == 0)
			struc->flag.nbr_zero = 1;
		return (ft_uintmax_t_itoa_base(tmp, 10));
	}
	else if (struc->lenght.j == 1)
	{
		tmp = va_arg(ap, intmax_t);
		if (tmp < 0)
		{
			struc->flag.negatif = 1;
			tmp = -tmp;
		}
		if (tmp == 0)
			struc->flag.nbr_zero = 1;
		return (ft_uintmax_t_itoa_base(tmp, 10));
	}
	return (modif_longeur_2(struc, ap, 0));
}

char		*modif_longeur_d_and_i(t_struc *struc, va_list ap)
{
	intmax_t	tmp;

	tmp = 0;
	if (struc->lenght.h == 1)
	{
		tmp = (short)va_arg(ap, int);
		if (tmp < 0)
		{
			struc->flag.negatif = 1;
			tmp = -tmp;
		}
		if (tmp == 0)
			struc->flag.nbr_zero = 1;
		return (ft_itoa(tmp));
	}
	return (modif_longeur_1(struc, ap, 0));
}
