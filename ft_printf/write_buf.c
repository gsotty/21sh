/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 09:49:55 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/21 15:49:29 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*write_buf_4(t_struc *struc, char *buf, t_len *len, va_list ap)
{
	if (struc->specifier.c == 1)
	{
		buf = write_c(struc, buf, len, ap);
		return (buf);
	}
	if (struc->specifier.cm == 1)
	{
		buf = write_cm(struc, buf, len, ap);
		return (buf);
	}
	if (struc->specifier.pourcent == 1)
	{
		buf = write_pourcent(struc, buf, len);
		return (buf);
	}
	if (struc->specifier.no_specifier == 1)
	{
		buf = write_no_specifier(struc, buf, len);
		return (buf);
	}
	return (NULL);
}

static char	*write_buf_3(t_struc *struc, char *buf, t_len *len, va_list ap)
{
	if (struc->specifier.um == 1)
	{
		buf = write_um(struc, buf, len, ap);
		return (buf);
	}
	if (struc->specifier.x == 1)
	{
		buf = write_x(struc, buf, len, ap);
		return (buf);
	}
	if (struc->specifier.xm == 1)
	{
		buf = write_xm(struc, buf, len, ap);
		return (buf);
	}
	if ((buf = write_buf_4(struc, buf, len, ap)) != NULL)
		return (buf);
	return (NULL);
}

static char	*write_buf_2(t_struc *struc, char *buf, t_len *len, va_list ap)
{
	if (struc->specifier.o == 1)
	{
		buf = write_o(struc, buf, len, ap);
		return (buf);
	}
	if (struc->specifier.om == 1)
	{
		buf = write_om(struc, buf, len, ap);
		return (buf);
	}
	if (struc->specifier.u == 1)
	{
		buf = write_u(struc, buf, len, ap);
		return (buf);
	}
	if ((buf = write_buf_3(struc, buf, len, ap)) != NULL)
		return (buf);
	return (NULL);
}

static char	*write_buf_1(t_struc *struc, char *buf, t_len *len, va_list ap)
{
	if (struc->specifier.d == 1)
	{
		buf = write_d_and_i(struc, buf, len, ap);
		return (buf);
	}
	if (struc->specifier.dm == 1)
	{
		buf = write_dm(struc, buf, len, ap);
		return (buf);
	}
	if (struc->specifier.i == 1)
	{
		buf = write_d_and_i(struc, buf, len, ap);
		return (buf);
	}
	if ((buf = write_buf_2(struc, buf, len, ap)) != NULL)
		return (buf);
	return (NULL);
}

char		*write_buf(t_struc *struc, char *buf, t_len *len, va_list ap)
{
	char*tmp;

	tmp = NULL;
	if (struc->specifier.s == 1)
	{
		buf = write_s(struc, buf, len, ap);
		return (buf);
	}
	if (struc->specifier.sm == 1)
	{
		buf = write_sm(struc, buf, len, ap);
		return (buf);
	}
	if (struc->specifier.p == 1)
	{
		buf = write_p(struc, buf, len, ap);
		return (buf);
	}
	if ((buf = write_buf_1(struc, buf, len, ap)) != NULL)
		return (buf);
	return (NULL);
}
