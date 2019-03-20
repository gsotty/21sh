/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:45:19 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/18 14:47:09 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

void	free_tab(char **tableau)
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