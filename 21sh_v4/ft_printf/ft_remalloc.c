/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 15:35:47 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/21 15:35:55 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_remalloc(char *dest, int len_d, int len_s)
{
	char	*tmp;

	if (len_d <= len_s)
		return (dest);
	if (!(tmp = (char *)malloc(sizeof(char) * len_d)))
		return (NULL);
	tmp = ft_memset(tmp, len_d, 0);
	tmp = ft_memcpy(tmp, dest, len_s);
	free(dest);
	dest = NULL;
	if (!(dest = (char *)malloc(sizeof(char) * len_d)))
		return (NULL);
	dest = ft_memset(dest, len_d, 0);
	dest = ft_memcpy(dest, tmp, len_d);
	dest[len_s] = '\0';
	free(tmp);
	return (dest);
}
