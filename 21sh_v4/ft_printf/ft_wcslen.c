/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcslen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 15:40:19 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/21 15:40:20 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <wchar.h>

size_t		ft_wcslen(const wchar_t *wcs)
{
	size_t		converted_char;
	int			current_char;
	char		temp[4];
	int			tmp;

	tmp = 0;
	converted_char = 0;
	while (*wcs)
	{
		if ((current_char = ft_wctomb(temp, *wcs++)) == -1)
			return ((size_t)-1);
		converted_char += current_char;
		tmp++;
	}
	return (converted_char);
}
