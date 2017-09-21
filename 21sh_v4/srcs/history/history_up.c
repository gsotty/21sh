/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_up.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 10:48:24 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/21 15:43:27 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int		history_up(t_pos *pos, t_history *history, struct winsize win,
		int modif_prompt)
{
	int		len_history;

	if (pos->history < history->len)
	{
		pos->history += 1;
		len_history = ft_strlen_lchar(history->history[pos->history]);
		pos->pos = len_history;
		pos->nbr_line = (len_of_nbr_ligne(win, pos->pos, modif_prompt) +
				nbr_new_line(history->history[pos->history]));
		pos->len = len_history;
		pos->len_malloc = len_history;
		new_safe_place(pos->len, nbr_new_line(history->history[pos->history]),
				modif_prompt);
		write_new_cmd(history->history[pos->history], pos, modif_prompt);
	}
	return (0);
}
