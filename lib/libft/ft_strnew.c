/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 17:15:16 by gsotty            #+#    #+#             */
/*   Updated: 2016/11/11 09:59:45 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	size_t	x;
	char	*tab;

	x = 0;
	tab = (char *)malloc(sizeof(char) * size + 1);
	while (tab == NULL)
		return (NULL);
	while (x <= size)
	{
		tab[x] = '\0';
		x++;
	}
	return (tab);
}
