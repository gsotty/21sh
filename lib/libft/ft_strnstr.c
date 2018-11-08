/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:57:38 by gsotty            #+#    #+#             */
/*   Updated: 2016/11/12 17:29:28 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		len2;
	char	*tabbig;
	char	*tablittle;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	tabbig = (char *)big;
	tablittle = (char *)little;
	len2 = ft_strlen(tablittle);
	while (tabbig[i] != '\0' && i <= len)
	{
		if ((ft_strncmp(tabbig + i, tablittle, len2) == 0) && (i + len2) <= len)
		{
			return (tabbig + i);
		}
		i++;
	}
	return (NULL);
}
