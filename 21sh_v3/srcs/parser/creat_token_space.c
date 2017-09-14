/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_token_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 12:04:17 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/07 15:10:02 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

t_token			*creat_token_space_bis(t_space *s, char *cmd, int type)
{
	int			end;

	end = 0;
	if (cmd[s->x] == ' ' && s->cut_space == 0)
	{
		end = s->x;
		s->cut_space = 1;
		return (token_new(cmd + s->start, end - s->start, type));
	}
	if (cmd[s->x] == ' ' && s->cut_space == 1)
	{
		while (cmd[s->x] == ' ' && cmd[s->x] != '\0')
			s->x++;
		end = s->x;
		s->cut_space = 0;
		return (token_new(cmd + s->start, end - s->start, type));
	}
	return (NULL);
}

t_token			*creat_token_space(char *cmd, int len, int first_call,
		int type)
{
	static t_space		s;
	t_token				*ret;

	if (first_call == 1)
		s.x = 0;
	s.start = s.x;
	while (s.x < len)
	{
		if (skip_quote_and_backslash(cmd, len, &s.x) == 0)
		{
			if ((ret = creat_token_space_bis(&s, cmd, type)))
				return (ret);
		}
		s.x++;
	}
	if (s.x == len)
	{
		s.x++;
		return (token_new(cmd + s.start, (s.x - 1) - s.start, type));
	}
	else
		return (NULL);
}
