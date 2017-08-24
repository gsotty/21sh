/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remalloc_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 15:38:47 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/24 14:12:31 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

char	*remalloc_cmd(t_len_cmd *len, char *cmd)
{
	char	*tmp;

	if (len->len >= len->len_cmd_malloc)
	{
		if ((tmp = ft_memalloc(sizeof(char) *
						(len->len_cmd_malloc + 3))) == NULL)
			return (NULL);
		ft_memcpy(tmp, cmd, len->len_cmd_malloc + 3);
		len->len_cmd_malloc += LEN_REMALLOC;
		free(cmd);
		if ((cmd = ft_memalloc(sizeof(char) *
						(len->len_cmd_malloc + 3))) == NULL)
			return (NULL);
		ft_memcpy(cmd, tmp, ((len->len_cmd_malloc + 3) - LEN_REMALLOC));
		free(tmp);
	}
	return (cmd);
}
