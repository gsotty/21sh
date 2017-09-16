/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_end.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 14:52:33 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/16 13:41:55 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

void	ft_key_end(t_lchar *cmd, t_pos *pos, t_len_cmd *len)
{
	struct winsize		win;

	ioctl(0, TIOCGWINSZ, &win);
	pos->pos = len->len;
	pos->nbr_line = (len_of_nbr_ligne(win, pos->pos) + nbr_new_line(cmd));
	new_safe_place(len->len, nbr_new_line(cmd));
	write_new_cmd(cmd, pos, len->len);
}
