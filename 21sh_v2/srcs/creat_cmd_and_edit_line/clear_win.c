/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_win.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 16:42:08 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/06 16:51:58 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

void	clear_win(char *cmd, t_len_cmd *len, t_pos *pos)
{
	tputs(tgetstr("cl", NULL), 0, f_putchar);
	write(0, _PROMPT, _PROMPT_LEN_WRITE);
	tputs(tgetstr("sc", NULL), 0, f_putchar);
	new_safe_place(len->len);
	write_new_cmd(cmd, pos, len->len);
}
