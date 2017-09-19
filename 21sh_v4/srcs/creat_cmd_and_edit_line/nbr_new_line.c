/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_new_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 13:28:32 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/19 12:23:16 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int		nbr_new_line(t_lchar *cmd)
{
	int		x;
	int		count;

	x = 0;
	count = 0;
	while (cmd[x].c != '\0')
	{
		if (cmd[x].type == _NEW_LINE)
			count++;
		x++;
	}
	return (count);
}
