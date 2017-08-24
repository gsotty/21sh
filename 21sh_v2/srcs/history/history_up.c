/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_up.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 10:48:24 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/24 15:48:11 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int		history_up(t_pos *pos, t_len_cmd *len, t_history *history,
		struct winsize win)
{
	int		len_history;

	if ((pos->history) < history->len)
	{
		pos->history += 1;
		len_history = ft_strlen(history->history[pos->history]);
		pos->pos = len_history;
		pos->nbr_line = len_of_nbr_ligne(win, pos->pos);
		len->len = len_history;
		len->len_cmd_malloc = len_history;
		new_safe_place(len->len);
		write_new_cmd(history->history[pos->history], pos, len_history);
	}
	return (0);
}
