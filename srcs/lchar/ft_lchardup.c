/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lchardup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:52:37 by gsotty            #+#    #+#             */
/*   Updated: 2019/04/05 11:11:53 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vingt_et_un_sh.h"
#include "../../include/lchar.h"

t_lchar			*ft_lchardup(t_lchar *dest, t_lchar *srs, int n)
{
	int		x;

	dest->len = srs->len + n;
	if ((dest->c = ft_memalloc(sizeof(char) * (dest->len + 1))) == NULL)
		return (NULL);
	if ((dest->type = ft_memalloc(sizeof(int) * (dest->len + 1))) == NULL)
		return (NULL);
	x = 0;
	while (x < srs->len)
	{
		dest->c[x] = srs->c[x];
		dest->type[x] = srs->type[x];
		x++;
	}
	while (x < dest->len)
	{
		dest->c[x] = 0;
		dest->type[x] = 0;
		x++;
	}
	return (dest);
}
