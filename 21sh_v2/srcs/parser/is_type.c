/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 11:32:38 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/07 09:56:23 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static int		only_space(char *cmd)
{
	int			x;
	int			y;

	x = 0;
	y = 0;
	while (cmd[x] != '\0')
	{
		if (cmd[x] == ' ')
			y++;
		x++;
	}
	if (y - x == 0)
		return (1);
	else
		return (0);
}

int				is_type(char *cmd, int nbr_token)
{
	if (cmd == NULL)
		return (_SPACE);
	else if (only_space(cmd) == 1)
		return (_SPACE);
	else if (cmd[0] == '\0')
		return (_SPACE);
	else if (nbr_token != 0 && nbr_token >= 1 && nbr_token <= 13)
		return (nbr_token);
	else
		return (_WORD);
}
