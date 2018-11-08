/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 10:13:42 by gsotty            #+#    #+#             */
/*   Updated: 2016/11/11 17:34:53 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	x;
	char	*tab;

	x = 0;
	if (s == NULL)
		return (NULL);
	if ((tab = (char *)malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	while (x < len)
	{
		tab[x] = s[start + x];
		x++;
	}
	tab[x] = '\0';
	return (tab);
}
