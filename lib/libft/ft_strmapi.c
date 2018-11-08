/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 09:45:56 by gsotty            #+#    #+#             */
/*   Updated: 2016/11/12 17:06:55 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		x;
	int		len;
	char	*tab;

	if (s == NULL || f == NULL)
		return (NULL);
	x = 0;
	len = ft_strlen(s);
	if ((tab = (char *)malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	while (s[x] != 0)
	{
		tab[x] = f(x, s[x]);
		x++;
	}
	tab[x] = '\0';
	return (tab);
}
