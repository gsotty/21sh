/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab_lchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 11:27:45 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/19 11:29:36 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

void	free_tab_lchar(t_lchar **tableau)
{
	int		x;

	x = 0;
	while (tableau[x] != NULL)
	{
		free(tableau[x]);
		x++;
	}
	free(tableau);
}
