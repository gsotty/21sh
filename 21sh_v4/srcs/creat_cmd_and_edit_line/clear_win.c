/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_win.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 16:42:08 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/19 14:51:53 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

void	clear_win(t_lchar *cmd, t_pos *pos, int modif_prompt)
{
	tputs(tgetstr("cl", NULL), 0, f_putchar);
	if (modif_prompt == NO_MODIF_PROMPT)
		write(0, _PROMPT, _PROMPT_LEN_WRITE);
	else
		write(0, _PROMPT_ML, _PROMPT_LEN_WRITE_ML);
	tputs(tgetstr("sc", NULL), 0, f_putchar);
	new_safe_place(pos->len, nbr_new_line(cmd));
	write_new_cmd(cmd, pos, modif_prompt);
}
