/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab_lchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 10:16:29 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/13 10:17:10 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

void	free_tab_lchar(t_lchar **tableau, int len_tab)
{
	int		x;

	x = 0;
	while (x < len_tab)
	{
		free(tableau[x]);
		tableau[x] = NULL;
		x++;
	}
	free(tableau);
}
