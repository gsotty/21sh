/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lcharlen_to_type.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 17:08:06 by gsotty            #+#    #+#             */
/*   Updated: 2017/10/04 17:16:10 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int			ft_lcharlen_to_type(t_lchar *cmd, int type)
{
	int		x;

	x = 0;
	while (cmd[x].c != '\0' && (cmd[x].type == type || cmd[x].type == 0))
		x++;
	return (x);
}
