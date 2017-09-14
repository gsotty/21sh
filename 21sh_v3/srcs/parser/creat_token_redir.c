/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_token_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 14:41:48 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/13 10:32:27 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

t_token		*creat_token_redir_bis(t_redir_token *s, char *cmd)
{
	if (cmd[s->x] == '>' && s->cut_rout == 0 && s->type == _WORD)
	{
		s->cut_rout = 1;
		return (token_new(cmd + s->start, s->x - s->start, s->type));
	}
	else if (cmd[s->x] == '>' && s->cut_rout == 1 && s->type == _WORD)
	{
		s->x++;
		s->cut_rout = 0;
		return (token_new(cmd + s->start, s->x - s->start, _ROUT));
	}
	if (cmd[s->x] == '<' && s->cut_rint == 0 && s->type == _WORD)
	{
		s->cut_rint = 1;
		return (token_new(cmd + s->start, s->x - s->start, s->type));
	}
	else if (cmd[s->x] == '<' && s->cut_rint == 1 && s->type == _WORD)
	{
		s->x++;
		s->cut_rint = 0;
		return (token_new(cmd + s->start, s->x - s->start, _RINT));
	}
	return (NULL);
}

t_token		*creat_token_redir(char *cmd, int len, int first_call, int type)
{
	static t_redir_token	s;
	t_token					*ret;

	s.type = type;
	if (first_call == 1)
		s.x = 0;
	s.start = s.x;
	while (s.x < len)
	{
		if (skip_quote_and_backslash(cmd, len, &s.x) == 0)
		{
			if ((ret = creat_token_redir_bis(&s, cmd)))
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
