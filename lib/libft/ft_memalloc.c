/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:23:24 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/07 19:26:24 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

#include <unistd.h>

void	*ft_memalloc(size_t size)
{
	size_t	x;
	void	*tab;

	x = 0;
	tab = malloc(size);
	if (tab == NULL)
		return (NULL);
	while (x < size)
	{
		((unsigned char *)tab)[x] = '\0';
		x++;
	}
	return (tab);
}
