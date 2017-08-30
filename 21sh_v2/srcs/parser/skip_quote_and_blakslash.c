/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quote_and_blakslash.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 14:36:28 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/30 14:36:56 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int			skip_quote_and_backslash(char *cmd, int len, int *count)
{
	if (cmd[*count] == '\\')
	{
		*count = *count + 1;
		return (1);
	}
	else if (cmd[*count] == '\'')
	{
		*count = *count + 1;
		while (cmd[*count] != '\'' && *count < len)
			*count = *count + 1;
		return (1);
	}
	else if (cmd[*count] == '\"')
	{
		*count = *count + 1;
		while (cmd[*count] != '\"' && *count < len)
			*count = *count + 1;
		return (1);
	}
	return (0);
}
