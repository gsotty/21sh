/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_character.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 15:10:59 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/21 10:18:35 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

void			ft_delete_character(t_lchar *cmd, t_pos *pos, int modif_prompt)
{
	t_lchar			*tmp;
	struct winsize	win;

	ioctl(0, TIOCGWINSZ, &win);
	if (pos->pos > 0)
	{
		tmp = ft_strdup_lchar(cmd + pos->pos);
		ft_memcpy_lchar(cmd + (pos->pos - 1), tmp, pos->len - pos->pos);
		pos->len--;
		pos->pos--;
		cmd[pos->len].c = '\0';
		pos->nbr_line = (len_of_nbr_ligne(win, pos->pos, modif_prompt) +
				nbr_new_line(cmd));
		new_safe_place(pos->len, nbr_new_line(cmd), modif_prompt);
		write_new_cmd(cmd, pos, modif_prompt);
		free(tmp);
	}
}
