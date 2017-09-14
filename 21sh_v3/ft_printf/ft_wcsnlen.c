/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcsnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 15:40:29 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/21 15:40:30 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <wchar.h>

size_t		ft_wcsnlen(const wchar_t *wcs, size_t n)
{
	size_t		converted_char;
	int			current_char;
	char		temp[4];

	converted_char = 0;
	while (wcs)
	{
		if ((current_char = ft_wctomb(temp, *wcs++)) == -1)
			return ((size_t)-1);
		if ((converted_char + current_char) > n)
			break ;
		converted_char += current_char;
	}
	return (converted_char);
}
