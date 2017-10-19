/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_creat_buf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 14:07:44 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/21 14:08:35 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

void		loop_creat_buf(int x, t_line *line, t_quote *quote)
{
	line[x].pos->is_quote = quote->is_quote;
	line[x].pos->is_dquote = quote->is_dquote;
	line[x].pos->is_backslash = quote->is_backslash;
}
