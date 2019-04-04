/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_onlyspace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 16:55:25 by gsotty            #+#    #+#             */
/*   Updated: 2019/04/04 16:55:57 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int		ft_onlyspace(int *type, int len)
{
	int		x;

	x = 0;
	while (x < len && (type[x] == _SPACE || type[x] == _NEW_LINE))
		x++;
	if (x == len)
		return (1);
	return (0);
}
