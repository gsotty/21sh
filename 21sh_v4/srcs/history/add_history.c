/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 09:09:36 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/18 15:48:47 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static int	add_history_no_word(t_history *history, t_lchar *cmd)
{
	history->history[history->len] = ft_strdup_lchar(cmd);
	history->len++;
	if (history->len >= history->len_malloc)
	{
		if (remalloc_history(history) == 1)
			return (1);
	}
	return (0);
}

int			add_history(t_history *history, t_lchar *cmd, int len)
{
	if (len > 0)
	{
		if (history->len - 1 > 0)
		{
			history->history[history->len] = ft_strdup_lchar(cmd);
			history->len++;
			if (history->len >= history->len_malloc)
			{
				if (remalloc_history(history) == 1)
					return (1);
			}
		}
		else
		{
			if (add_history_no_word(history, cmd) == 1)
				return (1);
		}
	}
	return (0);
}
