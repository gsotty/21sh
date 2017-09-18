/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_lchar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 09:19:03 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/18 15:43:53 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

size_t	ft_strlen_lchar(const t_lchar *s)
{
	size_t	x;

	x = 0;
	if (s == NULL)
		return (0);
	while (s[x].c != '\0')
	{
		x++;
	}
	return (x);
}
