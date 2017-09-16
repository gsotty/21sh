/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_down.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 10:45:36 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/16 13:43:01 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int		history_down(t_pos *pos, t_len_cmd *len, t_history *history,
		struct winsize win)
{
	int		len_history;

	if (pos->history > 0)
	{
		pos->history -= 1;
		len_history = ft_strlen_lchar(history->history[pos->history]);
		pos->pos = len_history;
		pos->nbr_line = (len_of_nbr_ligne(win, pos->pos) +
				nbr_new_line(history->history[pos->history]));
		len->len = len_history;
		len->len_cmd_malloc = len_history;
		new_safe_place(len->len, nbr_new_line(history->history[pos->history]));
		write_new_cmd(history->history[pos->history], pos, len_history);
	}
	return (0);
}
