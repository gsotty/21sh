/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 17:43:30 by gsotty            #+#    #+#             */
/*   Updated: 2017/10/04 17:47:03 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int		add_argv(t_creat_tree *a, t_cmd *cmd, t_lchar *str)
{
	int			tmp_pos;

	tmp_pos = a->pos;
	a->pos += ft_lcharlen_to_type(str + a->pos, _ARGV);
	if ((cmd->argv[a->argv] = ft_memalloc(sizeof(char) *
					(a->pos + 1))) == NULL)
		return (1);
	ft_memcpy_char_lchar(cmd->argv[a->argv], str + tmp_pos, a->pos - tmp_pos);
	a->argv++;
	return (0);
}
