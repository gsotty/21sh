/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 12:18:18 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/21 14:07:30 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static void	loop_verif_line(t_quote *quote, t_lchar *cmd, int x)
{
	if (quote->is_quote == 0 && quote->is_dquote == 0
			&& cmd[x].c == '\'')
		quote->is_quote = 1;
	else if (quote->is_quote == 1 && quote->is_dquote == 0
			&& cmd[x].c == '\'')
		quote->is_quote = 0;
	else if (quote->is_dquote == 0 && quote->is_quote == 0
			&& cmd[x].c == '\"')
		quote->is_dquote = 1;
	else if (quote->is_dquote == 1 && quote->is_quote == 0
			&& cmd[x].c == '\"')
		quote->is_dquote = 0;
}

int			verif_line(t_quote *quote, t_lchar *cmd)
{
	int		x;

	x = 0;
	quote->is_backslash = 0;
	while (cmd[x].c != '\0')
	{
		loop_verif_line(quote, cmd, x);
		if (cmd[x].c == '\\' && cmd[x + 1].c == '\n')
			quote->is_backslash = 1;
		else if (cmd[x + 1].c != '\0')
		{
			if (cmd[x].c == '\\')
				x++;
		}
		x++;
	}
	if (quote->is_quote == 1 || quote->is_dquote == 1 ||
			quote->is_backslash == 1)
		return (1);
	return (0);
}
