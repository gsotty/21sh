/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_cm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 16:01:17 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/21 16:01:18 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <wchar.h>

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

char		*write_cm(t_struc *struc, char *buf, t_len *len, va_list ap)
{
	char	*tmp;
	wchar_t	tmp_va;

	tmp_va = (wchar_t)va_arg(ap, int);
	tmp = ft_strnew(4);
	len->len_tmp = ft_wctomb(tmp, tmp_va);
	buf = ft_remalloc(buf, len->pos_buf + len->len_tmp, len->pos_buf);
	if (struc->width.number > len->len_tmp)
		tmp = ft_largeur(struc, tmp, len, struc->width.number - len->len_tmp);
	len->len_str += len->len_tmp;
	buf = ft_remalloc(buf, len->pos_buf + len->len_tmp, len->pos_buf);
	ft_memcpy(buf + len->pos_buf, tmp, len->len_tmp);
	len->pos_buf += len->len_tmp;
	free(tmp);
	return (buf);
}
