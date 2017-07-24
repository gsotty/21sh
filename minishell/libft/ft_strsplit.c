/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 16:01:14 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/06 15:02:56 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_mot(const char *s, char c)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (*s != '\0')
	{
		if (y == 1 && *s == c)
			y = 0;
		if (y == 0 && *s != c)
		{
			y = 1;
			x++;
		}
		s++;
	}
	return (x);
}

static int	ft_len_mot(const char *s, char c)
{
	int	len;

	len = 0;
	while (*s != c && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		nbr_mot;
	int		x;

	x = 0;
	if (s == NULL)
		return (NULL);
	nbr_mot = ft_mot((const char *)s, c);
	if ((tab = ft_memalloc(sizeof(*tab) * (ft_mot((const char *)s, c) + 1)))
			== NULL)
		return (NULL);
	while (nbr_mot--)
	{
		while (*s == c && *s != '\0')
			s++;
		tab[x] = ft_strsub((const char *)s, 0, ft_len_mot((const char *)s, c));
		if (tab[x] == NULL)
			return (NULL);
		s = s + ft_len_mot(s, c);
		x++;
	}
	return (tab);
}
