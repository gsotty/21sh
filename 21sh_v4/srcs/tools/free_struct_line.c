/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 15:27:49 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/20 15:43:35 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int		free_struct_line(t_line *line, int nbr_line)
{
	int		x;

	x = 0;
	while (x < nbr_line)
	{
		free(line[x].pos);
		free_tab_lchar(line[x].history->history);
		free(line[x].history);
		x++;
	}
	free(line);
	return (1);
}
