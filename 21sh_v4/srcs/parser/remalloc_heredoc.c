/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remalloc_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:54:32 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/27 16:56:03 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

char		*remalloc_heredoc(t_pos *len, char *cmd)
{
	char		*tmp;

	if (len->len >= len->len_malloc)
	{
		if ((tmp = ft_memalloc(sizeof(t_lchar) *
						(len->len_malloc + 3))) == NULL)
			return (NULL);
		ft_memcpy(tmp, cmd, len->len_malloc);
		len->len_malloc += LEN_REMALLOC;
		free(cmd);
		if ((cmd = ft_memalloc(sizeof(t_lchar) *
						(len->len_malloc + 3))) == NULL)
			return (NULL);
		ft_memcpy(cmd, tmp, ((len->len_malloc + 3) - LEN_REMALLOC));
		free(tmp);
	}
	return (cmd);
}
