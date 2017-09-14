/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 15:30:34 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/21 15:30:36 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_flag_1(char *tmp, t_len *len, char *str, size_t len_str)
{
	char	*tmp_char;

	tmp_char = NULL;
	tmp_char = ft_memalloc(len_str + 1);
	ft_memcpy(tmp_char, str, len_str + 1);
	tmp_char = ft_remalloc(tmp_char, len->len_tmp + len_str, len_str);
	ft_memcpy(tmp_char + len_str, tmp, len->len_tmp + len_str);
	free(tmp);
	tmp = NULL;
	tmp = ft_memalloc(len->len_tmp + len_str);
	ft_memcpy(tmp, tmp_char, len->len_tmp + len_str);
	free(tmp_char);
	len->len_tmp += len_str;
	return (tmp);
}
