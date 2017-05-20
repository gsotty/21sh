/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcstombs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 15:40:38 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/21 15:40:40 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <wchar.h>

size_t		ft_wcstombs(char *s, const wchar_t *wcs, size_t n)
{
	size_t		converted_char;
	int			current_char;
	int			i;
	char		temp[4];

	converted_char = 0;
	while (*wcs)
	{
		i = -1;
		ft_bzero(temp, 4);
		if ((current_char = ft_wctomb(temp, *wcs++)) == -1)
			return ((size_t)-1);
		if ((converted_char + current_char) <= n)
			while (++i < current_char)
				s[i] = temp[i];
		else
			break ;
		s += current_char;
		converted_char += current_char;
	}
	if (converted_char < n)
		*s = '\0';
	return (converted_char);
}
