/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_home.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 14:29:25 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/21 10:20:22 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

void	ft_key_home(t_lchar *cmd, t_pos *pos, int modif_prompt)
{
	struct winsize		win;

	ioctl(0, TIOCGWINSZ, &win);
	pos->pos = 0;
	pos->nbr_line = (len_of_nbr_ligne(win, pos->pos, modif_prompt) +
			nbr_new_line(cmd));
	new_safe_place(pos->len, nbr_new_line(cmd), modif_prompt);
	write_new_cmd(cmd, pos, modif_prompt);
}