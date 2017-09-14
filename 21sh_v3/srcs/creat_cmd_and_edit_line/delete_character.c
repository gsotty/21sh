/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_character.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 15:10:59 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/13 10:55:03 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

void			ft_delete_character(t_lchar *cmd, t_len_cmd *len,
		t_pos *pos)
{
	t_lchar			*tmp;
	struct winsize	win;

	ioctl(0, TIOCGWINSZ, &win);
	if (pos->pos > 0)
	{
		tmp = ft_strdup_lchar(cmd + pos->pos);
		ft_memcpy_lchar(cmd + (pos->pos - 1), tmp, len->len - pos->pos);
		len->len--;
		pos->pos--;
		cmd[len->len].c = '\0';
		pos->nbr_line = len_of_nbr_ligne(win, pos->pos);
		new_safe_place(len->len);
		write_new_cmd(cmd, pos, len->len);
		free(tmp);
	}
}
