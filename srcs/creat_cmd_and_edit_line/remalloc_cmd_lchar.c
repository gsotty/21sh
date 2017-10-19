/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remalloc_cmd_lchar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 10:11:53 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/29 13:23:20 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

t_lchar		*remalloc_cmd_lchar(t_pos *len, t_lchar *cmd)
{
	t_lchar		*tmp;

	if (len->len >= len->len_malloc)
	{
		if ((tmp = ft_memalloc(sizeof(t_lchar) *
						(len->len_malloc + 3))) == NULL)
			return (NULL);
		ft_memcpy_lchar(tmp, cmd, len->len_malloc);
		tmp[len->len_malloc].c = '\0';
		len->len_malloc += LEN_REMALLOC;
		free(cmd);
		if ((cmd = ft_memalloc(sizeof(t_lchar) *
						(len->len_malloc + 3))) == NULL)
			return (NULL);
		ft_memcpy_lchar(cmd, tmp, (len->len_malloc - LEN_REMALLOC));
		cmd[(len->len_malloc - LEN_REMALLOC)].c = '\0';
		free(tmp);
	}
	return (cmd);
}
