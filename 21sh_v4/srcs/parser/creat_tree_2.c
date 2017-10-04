/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_tree_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 17:05:32 by gsotty            #+#    #+#             */
/*   Updated: 2017/10/04 17:19:05 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static int		add_digit(t_creat_tree *a, t_redir *redir, t_lchar *cmd)
{
	int			tmp_pos;

	tmp_pos = a->pos;
	a->pos += ft_lcharlen_to_type(cmd + a->pos, _DIGIT);
	redir->digit = ft_atoi_lchar(cmd + tmp_pos);
	return (0);
}

static int		add_file_name(t_creat_tree *a, t_history *history,
		t_redir *redir, t_lchar *cmd)
{
	int			tmp_pos;
	char		buffer[4];

	tmp_pos = a->pos;
	a->pos += ft_lcharlen_to_type(cmd + a->pos, _FILE_NAME);
	if ((redir->file_name = ft_memalloc(sizeof(char) * (a->pos + 1))) == NULL)
		return (1);
	ft_memcpy_char_lchar(redir->file_name, cmd + tmp_pos, a->pos - tmp_pos);
	if (redir->type == _HEREDOC)
	{
		if ((redir->heredoc = convert_lchar_to_char(creat_heredoc(
							redir->file_name, LEN_REMAL_LI, buffer,
							history))) == NULL)
			return (1);
		redir->len_heredoc = ft_strlen(redir->file_name);
	}
	return (0);
}

int				creat_tree_2(t_creat_tree *a, t_exec *c, t_lchar *cmd,
		t_history *history)
{
	if (cmd[a->pos].type == _FILE_NAME)
	{
		if (add_file_name(a, history,
					c->sep[a->sep]->pipe[a->pipe]->redir[a->redir], cmd) == 1)
			return (1);
	}
	else if (cmd[a->pos].type == _DIGIT)
	{
		if (add_digit(a, c->sep[a->sep]->pipe[a->pipe]->redir[a->redir],
					cmd) == 1)
			return (1);
	}
	else if (cmd[a->pos].type == _TIRET)
	{
		c->sep[a->sep]->pipe[a->pipe]->redir[a->redir]->option = 1;
		a->pos++;
	}
	else
		a->pos++;
	return (0);
}
