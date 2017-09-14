/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_character_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 14:08:28 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/13 10:54:08 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

void			ft_delete_character_2(t_lchar *cmd, t_len_cmd *len,
		t_pos *pos)
{
	t_lchar			*tmp;
	struct winsize	win;

	ioctl(0, TIOCGWINSZ, &win);
	if (pos->pos < len->len)
	{
		tmp = ft_strdup_lchar(cmd + pos->pos);
		ft_memcpy_lchar(cmd + pos->pos, tmp + 1, len->len - pos->pos);
		len->len--;
		cmd[len->len].c = '\0';
		pos->nbr_line = len_of_nbr_ligne(win, pos->pos);
		new_safe_place(len->len);
		write_new_cmd(cmd, pos, len->len);
		free(tmp);
	}
}
