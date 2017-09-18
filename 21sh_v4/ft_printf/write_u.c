/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 14:14:12 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/22 09:23:31 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*modif_longeur(t_struc *struc, va_list ap)
{
	if (struc->lenght.h == 1)
		return (ft_unsigned_itoa((unsigned short)va_arg(ap, uintmax_t)));
	else if (struc->lenght.hh == 1)
		return (ft_unsigned_itoa((unsigned char)va_arg(ap, uintmax_t)));
	else if (struc->lenght.l == 1)
		return (ft_unsigned_long_itoa_base((long)va_arg(ap, uintmax_t), 10));
	else if (struc->lenght.ll == 1)
		return (ft_uintmax_t_itoa_base((long long)va_arg(ap, uintmax_t), 10));
	else if (struc->lenght.j == 1)
		return (ft_uintmax_t_itoa_base(va_arg(ap, uintmax_t), 10));
	else if (struc->lenght.z == 1)
		return (ft_unsigned_long_itoa_base((size_t)va_arg(ap, uintmax_t), 10));
	else
		return (ft_unsigned_itoa((unsigned int)va_arg(ap, unsigned int)));
}

static char	*ft_largeur(t_struc *struc, char *tmp, t_len *len, int tmp_int)
{
	char	*tmp_spaces;

	if (!(tmp_spaces = (char *)malloc(sizeof(char) * struc->width.number)))
		return (0);
	if (struc->flag.zero && (struc->flag.tiret == 0) &&
			(struc->precision.number == -1))
		ft_memset(tmp_spaces, 48, tmp_int);
	else
		ft_memset(tmp_spaces, 32, tmp_int);
	if (struc->flag.tiret)
	{
		tmp = ft_remalloc(tmp, struc->width.number, len->len_tmp);
		ft_memcpy(tmp + len->len_tmp, tmp_spaces, tmp_int);
	}
	else
	{
		tmp_spaces = ft_remalloc(tmp_spaces, struc->width.number, tmp_int);
		ft_memcpy(tmp_spaces + tmp_int, tmp, len->len_tmp);
		free(tmp);
		tmp = ft_memalloc(struc->width.number);
		ft_memcpy(tmp, tmp_spaces, struc->width.number);
	}
	len->len_tmp = struc->width.number;
	free(tmp_spaces);
	return (tmp);
}

static char	*ft_if_precision(t_struc *struc, char *tmp, t_len *len)
{
	char	*tmp_prec;

	tmp_prec = NULL;
	if (struc->precision.number > len->len_tmp)
	{
		if (!(tmp_prec = (char *)malloc(sizeof(char) *
						struc->precision.number)))
			return (0);
		ft_memset(tmp_prec, 48, struc->precision.number - len->len_tmp);
		tmp_prec[struc->precision.number - len->len_tmp] = '\0';
		tmp = ft_flag_1(tmp, len, tmp_prec, struc->precision.number -
				len->len_tmp);
	}
	if (struc->width.number > len->len_tmp)
		tmp = ft_largeur(struc, tmp, len, struc->width.number - len->len_tmp);
	len->len_str += len->len_tmp;
	free(tmp_prec);
	return (tmp);
}

static char	*ft_if_no_precision(t_struc *struc, char *tmp, t_len *len)
{
	if (struc->width.number > len->len_tmp)
		tmp = ft_largeur(struc, tmp, len, struc->width.number - len->len_tmp);
	len->len_str += len->len_tmp;
	return (tmp);
}

char		*write_u(t_struc *struc, char *buf, t_len *len, va_list ap)
{
	char	*tmp;

	tmp = modif_longeur(struc, ap);
	len->len_tmp = ft_strlen(tmp);
	if (ft_atoi(tmp) == 0 && struc->precision.number != -1 &&
			struc->width.number == 0)
		len->len_tmp = 0;
	if (struc->precision.number != -1)
		tmp = ft_if_precision(struc, tmp, len);
	else
		tmp = ft_if_no_precision(struc, tmp, len);
	buf = ft_remalloc(buf, len->pos_buf + len->len_tmp, len->pos_buf);
	ft_memcpy(buf + len->pos_buf, tmp, len->len_tmp);
	len->pos_buf += len->len_tmp;
	free(tmp);
	return (buf);
}
