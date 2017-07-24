/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 10:28:48 by gsotty            #+#    #+#             */
/*   Updated: 2016/11/12 17:12:16 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		x;
	int		lens1;
	int		lens2;
	char	*tab;

	x = -1;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	if ((tab = (char *)malloc(sizeof(char) * (lens1 + lens2) + 1)) == NULL)
		return (NULL);
	while (s1[++x] != '\0')
		tab[x] = s1[x];
	lens1 = 0;
	while (s2[lens1] != '\0')
	{
		tab[x] = s2[lens1];
		lens1++;
		x++;
	}
	tab[x] = '\0';
	return (tab);
}
