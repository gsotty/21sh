/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_token_gr_le.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 13:04:32 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/30 13:45:06 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

t_token		*creat_token_gr_le_bis(t_gr_le *s, char *cmd)
{
	if (cmd[s->x] == '>' && s->cut_gr == 0 && s->type != _DGREAT)
	{
		s->cut_gr = 1;
		return (token_new(cmd + s->start, s->x - s->start, 0));
	}
	if (cmd[s->x] == '>' && s->cut_gr == 1 && s->type != _DGREAT)
	{
		s->x++;
		s->cut_gr = 0;
		return (token_new(cmd + s->start, s->x - s->start, 0));
	}
	if (cmd[s->x] == '<' && s->cut_le == 0 && s->type != _DLESS)
	{
		s->cut_le = 1;
		return (token_new(cmd + s->start, s->x - s->start, 0));
	}
	if (cmd[s->x] == '<' && s->cut_le == 1 && s->type != _DLESS)
	{
		s->x++;
		s->cut_le = 0;
		return (token_new(cmd + s->start, s->x - s->start, 0));
	}
	return (NULL);
}

t_token		*creat_token_gr_le(char *cmd, int len, int first_call, int type)
{
	static t_gr_le	s;
	t_token			*ret;

	s.type = type;
	if (first_call == 1)
		s.x = 0;
	s.start = s.x;
	while (s.x < len)
	{
		if (skip_quote_and_backslash(cmd, len, &s.x) == 0)
		{
			if ((ret = creat_token_gr_le_bis(&s, cmd)))
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
