/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_token_sep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 14:40:35 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/13 12:40:05 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

t_token			*creat_token_sep_bis(t_lchar *cmd, int *x, int *cut_sep, int start)
{
	if (cmd[*x].c == ';' && *cut_sep == 0)
	{
		*cut_sep = 1;
		return (token_new(cmd + start, *x - start, 0));
	}
	else if (cmd[*x].c == ';' && *cut_sep == 1)
	{
		(*x)++;
		*cut_sep = 0;
		return (token_new(cmd + start, *x - start, _SEP));
	}
	return (NULL);
}

t_token			*creat_token_sep(t_lchar *cmd, int len, int first_call)
{
	static int	x;
	static int	cut_sep;
	int			start;
	t_token		*ret;

	if (first_call == 1)
		x = 0;
	start = x;
	while (x < len)
	{
		if (skip_quote_and_backslash(cmd, len, &x) == 0)
		{
			if ((ret = creat_token_sep_bis(cmd, &x, &cut_sep, start)))
				return (ret);
		}
		x++;
	}
	if (x == len)
	{
		x++;
		return (token_new(cmd + start, (x - 1) - start, 0));
	}
	else
		return (NULL);
}
