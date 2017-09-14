/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_of_nbr_ligne.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 14:46:04 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/06 15:15:57 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int			len_of_nbr_ligne(struct winsize win, int pos)
{
	int		nbr_ligne;
	int		tmp_pos;

	tmp_pos = pos;
	nbr_ligne = -1;
	while (tmp_pos > 0)
	{
		if (nbr_ligne == -1)
		{
			tmp_pos -= (win.ws_col - _PROMPT_LEN);
			nbr_ligne++;
		}
		else
		{
			tmp_pos -= win.ws_col;
			nbr_ligne++;
		}
	}
	return (nbr_ligne);
}
