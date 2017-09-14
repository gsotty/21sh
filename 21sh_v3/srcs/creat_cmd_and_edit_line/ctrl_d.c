/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 10:55:04 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/24 15:42:39 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int		ctrl_d(t_pos *pos, t_len_cmd *len, t_history *history)
{
	if (len->len == 0)
	{
		write(0, "exit\n", 5);
		free(history->history[pos->history]);
		return (1);
	}
	else
		ft_delete_character_2(history->history[pos->history], len, pos);
	return (0);
}
