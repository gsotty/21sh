/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 17:41:32 by gsotty            #+#    #+#             */
/*   Updated: 2017/10/04 17:42:03 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int			add_cmd(t_creat_tree *a, t_cmd *cmd, t_lchar *str)
{
	int		tmp_pos;

	tmp_pos = a->pos;
	a->pos += ft_lcharlen_to_type(str + a->pos, _CMD);
	if ((cmd->exec = ft_memalloc(sizeof(char) *
					(a->pos + 1))) == NULL)
		return (1);
	ft_memcpy_char_lchar(cmd->exec,
			str + tmp_pos, a->pos - tmp_pos);
	if ((cmd->argv[a->argv] =
				ft_memalloc(sizeof(char) * (a->pos + 1))) == NULL)
		return (1);
	ft_memcpy_char_lchar(cmd->argv[a->argv],
			str + tmp_pos, a->pos - tmp_pos);
	a->argv = a->argv + 1;
	return (0);
}
