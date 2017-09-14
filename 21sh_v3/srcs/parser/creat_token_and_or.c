/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_token_and_or.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 14:10:28 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/06 14:00:35 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

t_token			*creat_token_and_or_bis(t_and_or *s, char *cmd)
{
	if (cmd[s->x] == '|' && cmd[s->x + 1] == '|' && s->cut_or == 0)
	{
		s->cut_or = 1;
		return (token_new(cmd + s->start, s->x - s->start, 0));
	}
	else if (cmd[s->x] == '|' && cmd[s->x + 1] == '|' && s->cut_or == 1)
	{
		s->x = s->x + 2;
		s->cut_or = 0;
		return (token_new(cmd + s->start, s->x - s->start, 0));
	}
	else if (cmd[s->x] == '&' && cmd[s->x + 1] == '&' && s->cut_and == 0)
	{
		s->cut_and = 1;
		return (token_new(cmd + s->start, s->x - s->start, 0));
	}
	else if (cmd[s->x] == '&' && cmd[s->x + 1] == '&' && s->cut_and == 1)
	{
		s->x = s->x + 2;
		s->cut_and = 0;
		return (token_new(cmd + s->start, s->x - s->start, 0));
	}
	return (NULL);
}

t_token			*creat_token_and_or(char *cmd, int len, int first_call)
{
	static t_and_or		s;
	t_token				*ret;

	if (first_call == 1)
		s.x = 0;
	s.start = s.x;
	while (s.x < len)
	{
		if (skip_quote_and_backslash(cmd, len, &s.x) == 0)
		{
			if ((ret = creat_token_and_or_bis(&s, cmd)))
				return (ret);
		}
		s.x++;
	}
	if (s.x == len)
	{
		s.x++;
		return (token_new(cmd + s.start, (s.x - 1) - s.start, 0));
	}
	else
		return (NULL);
}
