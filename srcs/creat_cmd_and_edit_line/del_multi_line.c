/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_multi_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 11:28:27 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/19 14:55:33 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

void		del_multi_line(char *buffer, t_lchar *cmd, t_pos *pos,
		int modif_prompt)
{
	ft_memset(buffer, 0, sizeof(*buffer) * 4);
	read(0, buffer, 3);
	if (buffer[0] == 126 && buffer[1] == 0 && buffer[2] == 0)
		ft_delete_character_2(cmd, pos, modif_prompt);
}
