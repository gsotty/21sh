/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_token_dg_dl.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 13:46:11 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/30 13:55:43 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

t_token			*creat_token_dg_dl_bis(t_dg_dl *s, char *cmd)
{
	if (cmd[s->x] == '>' && cmd[s->x + 1] == '>' && s->cut_dgreat == 0)
	{
		s->cut_dgreat = 1;
		return (token_new(cmd + s->start, s->x - s->start, 0));
	}
	else if (cmd[s->x] == '>' && cmd[s->x + 1] == '>' && s->cut_dgreat == 1)
	{
		s->x = s->x + 2;
		s->cut_dgreat = 0;
		return (token_new(cmd + s->start, s->x - s->start, 0));
	}
	else if (cmd[s->x] == '<' && cmd[s->x + 1] == '<' && s->cut_dless == 0)
	{
		s->cut_dless = 1;
		return (token_new(cmd + s->start, s->x - s->start, 0));
	}
	else if (cmd[s->x] == '<' && cmd[s->x + 1] == '<' && s->cut_dless == 1)
	{
		s->x = s->x + 2;
		s->cut_dless = 0;
		return (token_new(cmd + s->start, s->x - s->start, 0));
	}
	return (NULL);
}

t_token			*creat_token_dg_dl(char *cmd, int len, int first_call)
{
	static t_dg_dl	s;
	t_token			*ret;

	if (first_call == 1)
		s.x = 0;
	s.start = s.x;
	while (s.x < len)
	{
		if (skip_quote_and_backslash(cmd, len, &s.x) == 0)
		{
			if ((ret = creat_token_dg_dl_bis(&s, cmd)))
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
