/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_cpy_his.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 14:54:56 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/17 16:14:54 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./vingt_et_un_sh.h"

char	**creat_cpy_his(t_history *history)
{
	char	**tmp;
	int		x;

	x = 0;
	if ((tmp = ft_memalloc(sizeof(char *) * (history->len + 2))) == NULL)
		return (NULL);
	while (x < history->len)
	{
		tmp[x] = ft_strdup(history->history[x]);
		x++;
	}
	tmp[x] = NULL;
	return (tmp);
}
