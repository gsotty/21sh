/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remalloc_cmd_lchar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 10:11:53 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/13 10:14:58 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

t_lchar		*remalloc_cmd_lchar(t_len_cmd *len, t_lchar *cmd)
{
	t_lchar		*tmp;

	if (len->len >= len->len_cmd_malloc)
	{
		if ((tmp = ft_memalloc(sizeof(t_lchar) *
						(len->len_cmd_malloc + 3))) == NULL)
			return (NULL);
		ft_memcpy_lchar(tmp, cmd, len->len_cmd_malloc);
		len->len_cmd_malloc += LEN_REMALLOC;
		free(cmd);
		if ((cmd = ft_memalloc(sizeof(t_lchar) *
						(len->len_cmd_malloc + 3))) == NULL)
			return (NULL);
		ft_memcpy_lchar(cmd, tmp, ((len->len_cmd_malloc + 3) - LEN_REMALLOC));
		free(tmp);
	}
	return (cmd);
}
