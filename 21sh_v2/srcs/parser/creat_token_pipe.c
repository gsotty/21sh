/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_token_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 13:58:41 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/07 15:29:27 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

t_token			*creat_token_pipe_bis(t_pipe *s, char *cmd)
{
	if (cmd[s->x] == '|' && s->cut_pipe == 0)
	{
		s->cut_pipe = 1;
		return (token_new(cmd + s->start, s->x - s->start, s->type));
	}
	if (cmd[s->x] == '|' && s->cut_pipe == 1)
	{
		s->x++;
		s->cut_pipe = 0;
		return (token_new(cmd + s->start, s->x - s->start, _PIPE));
	}
	return (NULL);
}

t_token			*creat_token_pipe(char *cmd, int len, int first_call, int type)
{
	static t_pipe	s;
	t_token			*ret;

	s.type = type;
	if (first_call == 1)
		s.x = 0;
	s.start = s.x;
	while (s.x < len)
	{
		if (skip_quote_and_backslash(cmd, len, &s.x) == 0)
		{
			if ((ret = creat_token_pipe_bis(&s, cmd)))
				return (ret);
		}
		s.x++;
	}
	if (s.x == len)
	{
		s.x++;
		return (token_new(cmd + s.start, (s.x - 1) - s.start, s.type));
	}
	else
		return (NULL);
}
