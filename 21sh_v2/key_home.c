/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_home.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 14:29:25 by gsotty            #+#    #+#             */
/*   Updated: 2017/07/26 14:32:50 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./vingt_et_un_sh.h"

void	ft_key_home(char *cmd, t_pos *pos, t_len_cmd *len)
{
	struct winsize		win;

	ioctl(0, TIOCGWINSZ, &win);
	pos->pos = 0;
	pos->nbr_line = len_of_nbr_ligne(win, pos->pos);
	new_safe_place(len->len);
	write_new_cmd(cmd, pos, len->len);
}
