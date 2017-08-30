/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_token_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 12:04:17 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/30 13:03:09 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

t_token			*creat_token_space_bis(int *x, char *cmd, int *cut_space,
		int start)
{
	int		end;

	end = 0;
	if (cmd[*x] == ' ' && *cut_space == 0)
	{
		end = *x;
		*cut_space = 1;
		return (token_new(cmd + start, end - start, 0));
	}
	if (cmd[*x] == ' ' && *cut_space == 1)
	{
		while (cmd[*x] == ' ' && cmd[*x] != '\0')
			(*x)++;
		end = *x;
		*cut_space = 0;
		return (token_new(cmd + start, end - start, 0));
	}
	return (NULL);
}

t_token			*creat_token_space(char *cmd, int len, int first_call)
{
	static int	x;
	static int	cut_space;
	int			start;
	t_token		*ret;

	if (first_call == 1)
		x = 0;
	start = x;
	while (x < len)
	{
		if (skip_quote_and_backslash(cmd, len, &x) == 0)
		{
			if ((ret = creat_token_space_bis(&x, cmd, &cut_space, start)))
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
