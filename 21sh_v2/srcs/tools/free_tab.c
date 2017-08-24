/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 13:43:30 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/24 14:15:46 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

void	free_tab(char **tableau, int len_tab)
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
