/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 09:09:36 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/17 13:10:26 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./vingt_et_un_sh.h"

int		add_history(t_history *history, char *cmd, int len)
{
	if (len > 0)
	{
		if (history->len - 1 > 0)
		{
			if (ft_strcmp(cmd, history->history[history->len - 1]) != 0)
			{
				history->history[history->len] = ft_strdup(cmd);
				history->len++;
				if (history->len >= history->len_malloc)
				{
					if (remalloc_history(history) == 1)
						return (1);
				}
			}
		}
		else
		{
			history->history[history->len] = ft_strdup(cmd);
			history->len++;
			if (history->len >= history->len_malloc)
			{
				if (remalloc_history(history) == 1)
					return (1);
			}
		}
	}
	return (0);
}
