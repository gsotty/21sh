/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_new_line_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 14:28:21 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/28 14:35:26 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int		nbr_new_line_heredoc(char *cmd)
{
	int		x;
	int		count;

	x = 0;
	count = 0;
	while (cmd[x] != '\0')
	{
		if (cmd[x] == '\n')
			count++;
		x++;
	}
	return (count);
}
