/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   approut_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 14:02:49 by gsotty            #+#    #+#             */
/*   Updated: 2017/10/04 14:04:15 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

void		approut_heredoc(int type, t_define_lchar *struct_var, t_lchar *cmd)
{
	cmd[struct_var->x].type = type;
	cmd[struct_var->x + 1].type = type;
	struct_var->is_redir = 1;
	struct_var->is_digit = 0;
	rep_nbr(struct_var->x, cmd);
}
