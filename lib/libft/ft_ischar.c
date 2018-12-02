/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ischar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 13:06:54 by gsotty            #+#    #+#             */
/*   Updated: 2018/12/02 13:08:10 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ischar(const char str, const char *c)
{
	int		x;

	x = 0;
	while (c[x] != '\0')
	{
		if (c[x] == str)
			return (1);
		x++;
	}
	return (0);
}
