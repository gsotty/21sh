/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lcharndup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:02:18 by gsotty            #+#    #+#             */
/*   Updated: 2019/04/04 15:03:26 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

t_lchar			*ft_lcharndup(t_lchar *src, int start, int end)
{
	int			x;
	t_lchar		*dest;

	if ((dest = ft_memalloc(sizeof(t_lchar))) == NULL)
		return (NULL);
	dest->len = (end - start) + 1;
	if ((dest->c = ft_memalloc(sizeof(char) * (dest->len + 1))) == NULL)
		return (NULL);
	if ((dest->type = ft_memalloc(sizeof(int) * (dest->len + 1))) == NULL)
		return (NULL);
	x = 0;
	while (x < dest->len)
	{
		dest->c[x] = src->c[x + start];
		dest->type[x] = src->type[x + start];
		x++;
	}
	dest->c[x] = '\0';
	dest->type[x] = 0;
	return (dest);
}
