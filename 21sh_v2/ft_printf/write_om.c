/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_om.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 13:37:17 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/21 16:31:41 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_largeur(t_struc *struc, char *tmp, t_len *len, int tmp_int)
{
	char	*tmp_spaces;

	if (!(tmp_spaces = (char *)malloc(sizeof(char) * struc->width.number)))
		return (0);
	if ((struc->flag.zero == 1) && (struc->flag.tiret == 0) &&
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
	if (struc->flag.diese == 1)
		tmp = ft_flag_1(tmp, len, "0", 1);
	if (struc->width.number > len->len_tmp)
		tmp = ft_largeur(struc, tmp, len, struc->width.number - len->len_tmp);
	len->len_str += len->len_tmp;
	free(tmp_prec);
	return (tmp);
}

static char	*ft_if_no_precision(t_struc *struc, char *tmp, t_len *len)
{
	if (struc->flag.diese == 1)
		tmp = ft_flag_1(tmp, len, "0", 1);
	if (struc->width.number > len->len_tmp)
		tmp = ft_largeur(struc, tmp, len, struc->width.number - len->len_tmp);
	len->len_str += len->len_tmp;
	return (tmp);
}

char		*write_om(t_struc *struc, char *buf, t_len *len, va_list ap)
{
	char	*tmp;

	tmp = modif_longeur_om(struc, ap);
	len->len_tmp = ft_strlen(tmp);
	if (struc->flag.nbr_zero == 1 && (struc->width.number != 0 ||
				struc->precision.number != -1) && struc->flag.diese != 1)
		len->len_tmp = 0;
	if (struc->flag.nbr_zero == 1)
		struc->flag.diese = 0;
	if (struc->flag.diese == 1 && struc->precision.number > 0)
		struc->precision.number = struc->precision.number - 1;
	buf = ft_remalloc(buf, len->len_str + len->len_tmp, len->pos_buf);
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
