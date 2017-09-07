/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_token_appredir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 14:35:18 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/07 15:23:55 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

t_token			*creat_token_appredir_bis(t_appredir *s, char *cmd)
{
	if (cmd[s->x] == '>' && cmd[s->x + 1] == '&' && s->cut_dup_output == 0)
	{
		s->cut_dup_output = 1;
		return (token_new(cmd + s->start, s->x - s->start, 0));
	}
	else if (cmd[s->x] == '>' && cmd[s->x + 1] == '&' && s->cut_dup_output == 1)
	{
		s->x = s->x + 2;
		s->cut_dup_output = 0;
		return (token_new(cmd + s->start, s->x - s->start, _DUP_OUTPUT));
	}
	if (cmd[s->x] == '<' && cmd[s->x + 1] == '&' && s->cut_dup_input == 0)
	{
		s->cut_dup_input = 1;
		return (token_new(cmd + s->start, s->x - s->start, 0));
	}
	else if (cmd[s->x] == '<' && cmd[s->x + 1] == '&' && s->cut_dup_input == 1)
	{
		s->x = s->x + 2;
		s->cut_dup_input = 0;
		return (token_new(cmd + s->start, s->x - s->start, _DUP_INPUT));
	}
	if (cmd[s->x] == '&' && cmd[s->x + 1] == '>' && s->cut_routerr == 0)
	{
		s->cut_routerr = 1;
		return (token_new(cmd + s->start, s->x - s->start, 0));
	}
	else if (cmd[s->x] == '&' && cmd[s->x + 1] == '>' && s->cut_routerr == 1)
	{
		s->x = s->x + 2;
		s->cut_routerr = 0;
		return (token_new(cmd + s->start, s->x - s->start, _ROUTERR));
	}
	if (cmd[s->x] == '>' && cmd[s->x + 1] == '>' && s->cut_approut == 0)
	{
		s->cut_approut = 1;
		return (token_new(cmd + s->start, s->x - s->start, 0));
	}
	else if (cmd[s->x] == '>' && cmd[s->x + 1] == '>' && s->cut_approut == 1)
	{
		s->x = s->x + 2;
		s->cut_approut = 0;
		return (token_new(cmd + s->start, s->x - s->start, _APPROUT));
	}
	else if (cmd[s->x] == '<' && cmd[s->x + 1] == '<' && s->cut_heredoc == 0)
	{
		s->cut_heredoc = 1;
		return (token_new(cmd + s->start, s->x - s->start, 0));
	}
	else if (cmd[s->x] == '<' && cmd[s->x + 1] == '<' && s->cut_heredoc == 1)
	{
		s->x = s->x + 2;
		s->cut_heredoc = 0;
		return (token_new(cmd + s->start, s->x - s->start, _HEREDOC));
	}
	return (NULL);
}

t_token			*creat_token_appredir(char *cmd, int len, int first_call,
		int type)
{
	static t_appredir	s;
	t_token				*ret;

	s.type = type;
	if (first_call == 1)
		s.x = 0;
	s.start = s.x;
	while (s.x < len)
	{
		if (skip_quote_and_backslash(cmd, len, &s.x) == 0)
		{
			if ((ret = creat_token_appredir_bis(&s, cmd)))
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
