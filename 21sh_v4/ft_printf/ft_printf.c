/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 09:39:00 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/13 12:16:11 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	verif_line_2(t_struc *struc, int z, int y, va_list ap)
{
	check_flag(struc, z, y);
	check_width(struc, z, y, ap);
	check_precision(struc, z, y, ap);
	check_lenght(struc, z, y);
}

static char	*ft_no_pourcent(t_len *len, const char *str, char *buf)
{
	buf = ft_remalloc(buf, len->pos_buf + 1, len->pos_buf);
	buf[len->pos_buf++] = str[len->pos_str++];
	return (buf);
}

static char	*verif_line(t_len *len, const char *str, char *buf, va_list ap)
{
	int		y;
	t_struc	struc;

	y = 0;
	while (str[len->pos_str] != '\0')
	{
		if (str[len->pos_str] == '%' && (y = len->pos_str + 1))
		{
			ft_bzero(&struc, sizeof(t_struc));
			struc.str = ft_strdup((char *)str);
			len->pos_str = check_specifier(&struc, str, len->pos_str + 1);
			verif_line_2(&struc, len->pos_str, y, ap);
			buf = write_buf(&struc, buf, len, ap);
			len->pos_str++;
			free(struc.str);
		}
		else
			buf = ft_no_pourcent(len, str, buf);
	}
	return (buf);
}

int			ft_printf(const char *str, ...)
{
	t_len	len;
	va_list	ap;
	char	*buf;

	buf = NULL;
	ft_memset(&len, 0, sizeof(t_len));
	len.len_str = ft_strlen((char *)str);
	va_start(ap, str);
	if ((buf = ft_strnew(len.len_str)) == NULL)
		return (-1);
	ft_memset(buf, 0, len.len_str);
	if ((buf = verif_line(&len, str, buf, ap)) == NULL)
		return (0);
	ft_putnstr(buf, len.pos_buf);
	va_end(ap);
	if (len.null == 1)
		len.pos_buf = -1;
	free(buf);
	return (len.pos_buf);
}
