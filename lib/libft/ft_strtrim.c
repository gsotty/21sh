/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 10:56:23 by gsotty            #+#    #+#             */
/*   Updated: 2016/11/12 17:20:23 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s)
{
	int		x;
	int		y;
	int		len;
	char	*tab;

	x = 0;
	y = 0;
	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	while ((s[x] == ' ' || s[x] == ',' || s[x] == '\n' || s[x] == '\t') && s[x])
		x++;
	while ((s[len - 1] == ' ' || s[len - 1] == ',' || s[len - 1] == '\n' ||
			s[len - 1] == '\t') && x < len)
		len--;
	if ((tab = (char *)malloc(sizeof(char) * (len - x) + 1)) == NULL)
		return (NULL);
	while (x < len)
	{
		tab[y] = s[x];
		x++;
		y++;
	}
	tab[y] = '\0';
	return (tab);
}
