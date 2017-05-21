/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 10:46:09 by gsotty            #+#    #+#             */
/*   Updated: 2016/11/10 13:13:08 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	int		x;
	size_t	len;
	char	*dest;

	x = 0;
	len = ft_strlen(s);
	if ((dest = (char *)malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	while (s[x] != '\0')
	{
		dest[x] = s[x];
		x++;
	}
	dest[x] = '\0';
	return (dest);
}
