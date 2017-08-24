/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_character.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 15:10:59 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/24 15:44:10 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

void			ft_delete_character(char *cmd, t_len_cmd *len,
		t_pos *pos)
{
	char			*tmp;
	struct winsize	win;

	ioctl(0, TIOCGWINSZ, &win);
	if (pos->pos > 0)
	{
		tmp = ft_strdup(cmd + pos->pos);
		ft_memcpy(cmd + (pos->pos - 1), tmp, len->len - pos->pos);
		len->len--;
		pos->pos--;
		cmd[len->len] = '\0';
		pos->nbr_line = len_of_nbr_ligne(win, pos->pos);
		new_safe_place(len->len);
		write_new_cmd(cmd, pos, len->len);
		free(tmp);
	}
}
