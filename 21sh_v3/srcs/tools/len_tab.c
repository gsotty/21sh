/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 13:42:06 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/24 14:16:34 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int		len_tab(char **tableau)
{
	int		x;

	x = 0;
	while (tableau[x] != NULL)
	{
		x++;
	}
	return (x);
}
