/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:38:22 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/21 17:08:32 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_largeur(t_struc *struc, char *tmp, t_len *len, int tmp_int)
{
	char	*tmp_spaces;

	if (!(tmp_spaces = ft_memalloc(sizeof(char) * struc->width.number)))
		return (0);
	if ((struc->flag.zero == 1) && (struc->flag.tiret == 0) &&
			(struc->precision.number <= 0))
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
	if (struc->precision.number <= len->len_tmp)
	{
		tmp = ft_remalloc(tmp, struc->precision.number, len->len_tmp);
		tmp[struc->precision.number] = '\0';
		len->len_tmp = struc->precision.number;
	}
	if (struc->width.number > len->len_tmp)
		tmp = ft_largeur(struc, tmp, len, struc->width.number - len->len_tmp);
	len->len_str += len->len_tmp;
	return (tmp);
}

static char	*ft_if_no_precision(t_struc *struc, char *tmp, t_len *len)
{
	if (struc->width.number > len->len_tmp)
		tmp = ft_largeur(struc, tmp, len, struc->width.number - len->len_tmp);
	len->len_str += len->len_tmp;
	return (tmp);
}

static char	*conv_char(t_struc *struc, va_list ap, t_len *len)
{
	size_t	x;
	char	*tmp;
	wchar_t	*tmp_va;

	tmp_va = va_arg(ap, int *);
	if (tmp_va == NULL)
	{
		tmp = ft_memalloc(7);
		ft_memcpy(tmp, "(null)", 7);
		len->len_tmp = 6;
	}
	if (tmp_va != NULL)
	{
		if (struc->precision.number == -1)
			x = ft_wcslen(tmp_va);
		else
			x = ft_wcsnlen(tmp_va, struc->precision.number);
		tmp = ft_memalloc(x);
		len->len_tmp = ft_wcstombs(tmp, tmp_va, x);
	}
	return (tmp);
}

char		*write_sm(t_struc *struc, char *buf, t_len *len, va_list ap)
{
	char	*tmp;

	tmp = conv_char(struc, ap, len);
	if (tmp[0] == '\0')
		struc->precision.number = -1;
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
