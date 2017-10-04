/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 16:25:03 by gsotty            #+#    #+#             */
/*   Updated: 2017/10/04 17:47:01 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static int	add_fd(t_creat_tree *a, t_redir **redir, t_lchar *cmd)
{
	int		tmp_pos;

	tmp_pos = a->pos;
	a->pos += ft_lcharlen_to_type(cmd + a->pos, _FD);
	redir[a->redir + 1]->fd = ft_atoi_lchar(cmd + tmp_pos);
	return (0);
}

static void	reset_sep(t_creat_tree *a)
{
	a->argv = 0;
	a->pipe = 0;
	a->redir = -1;
	a->pos++;
	a->sep++;
}

static void	reset_pipe(t_creat_tree *a)
{
	a->argv = 0;
	a->redir = -1;
	a->pipe++;
	a->pos++;
}

static void	add_redir_tow(t_creat_tree *a, t_exec *c, t_lchar *cmd)
{
	c->sep[a->sep]->pipe[a->pipe]->redir[a->redir]->type = cmd[a->pos].type;
	a->pos++;
}

int			creat_tree(t_creat_tree *a, t_exec *c, t_lchar *cmd,
		t_history *history)
{
	while (cmd[a->pos].c != '\0')
	{
		if (cmd[a->pos].type == _SEP)
			reset_sep(a);
		else if (cmd[a->pos].type == _PIPE)
			reset_pipe(a);
		else if (cmd[a->pos].type == _RINT || cmd[a->pos].type == _ROUT)
			c->sep[a->sep]->pipe[a->pipe]->redir[a->redir]->type =
				cmd[a->pos].type;
		else if (cmd[a->pos].type == 6 || cmd[a->pos].type == 7 ||
				cmd[a->pos].type == 10 || cmd[a->pos].type == 11 ||
				cmd[a->pos].type == 12)
			add_redir_tow(a, c, cmd);
		else if (cmd[a->pos].type == _CMD)
			a->rep = add_cmd(a, &c->sep[a->sep]->pipe[a->pipe]->cmd, cmd);
		else if (cmd[a->pos].type == _ARGV)
			a->rep = add_argv(a, &c->sep[a->sep]->pipe[a->pipe]->cmd, cmd);
		else if (cmd[a->pos].type == _FD)
			a->rep = add_fd(a, c->sep[a->sep]->pipe[a->pipe]->redir, cmd);
		else
			a->rep = creat_tree_2(a, c, cmd, history);
		if (a->rep == 1)
			return (1);
	}
	return (0);
}
