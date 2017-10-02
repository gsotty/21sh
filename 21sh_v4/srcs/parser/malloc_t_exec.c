/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_t_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 15:00:55 by gsotty            #+#    #+#             */
/*   Updated: 2017/10/02 14:24:31 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static int		len_redir(t_lchar *cmd, int sep, int pipe)
{
	int		x;
	int		redir;
	int		sep_verif;
	int		pipe_verif;

	x = 0;
	redir = 0;
	sep_verif = 0;
	pipe_verif = 0;
	while (cmd[x].c != '\0')
	{
		if ((cmd[x].type == _RINT || cmd[x].type == _ROUT)
				&& sep_verif == sep && pipe_verif == pipe)
		{
			redir++;
			x++;
		}
		else if ((cmd[x].type ==  _APPROUT || cmd[x].type == _HEREDOC ||
					cmd[x].type == _DUP_RINT || cmd[x].type == _DUP_ROUT ||
					cmd[x].type == _ROUTERR) && sep_verif == sep && pipe_verif
				== pipe)
		{
			redir++;
			x = x + 2;
		}
		else if (cmd[x].type == _SEP)
		{
			sep_verif++;
			x++;
		}
		else if (cmd[x].type == _PIPE)
		{
			pipe_verif++;
			x++;
		}
		else
			x++;
	}
	return (redir);
}

static int		malloc_t_exec_redir(t_exec *c, int redir,
		int x, int y)
{
	int		z;

	z = 0;
	if ((c->sep[x]->pipe[y]->redir =
				ft_memalloc(sizeof(*c->sep[x]->pipe[y]->redir) *
					(redir + 1))) == NULL)
		return (1);
	while (z < redir)
	{
		if ((c->sep[x]->pipe[y]->redir[z] =
					ft_memalloc(sizeof(*c->sep[x]->pipe[y]->redir[z]))) == NULL)
			return (1);
		c->sep[x]->pipe[y]->redir[z]->fd = -1;
		c->sep[x]->pipe[y]->redir[z]->digit = -1;
		c->sep[x]->pipe[y]->redir[z]->len_heredoc = -1;
		c->sep[x]->pipe[y]->redir[z]->type = -1;
		z++;
	}
	return (0);
}

static int		len_pipe(t_lchar *cmd, int sep)
{
	int		x;
	int		pipe;
	int		sep_verif;

	x = 0;
	pipe = 1;
	sep_verif = 0;
	while (cmd[x].c != '\0')
	{
		if (cmd[x].type == _PIPE && sep_verif == sep)
			pipe++;
		else if (cmd[x].type == _SEP)
			sep_verif++;
		x++;
	}
	return (pipe);
}

static int		malloc_t_exec_pipe(t_lchar *cmd, t_exec *c, int pipe, int x)
{
	int		y;
	int		redir;

	y = 0;
	if ((c->sep[x]->pipe = ft_memalloc(sizeof(*c->sep[x]->pipe) *
					(pipe + 1))) == NULL)
		return (1);
	while (y < pipe)
	{
		redir = len_redir(cmd, x, y);
		if ((c->sep[x]->pipe[y] = ft_memalloc(sizeof(*c->sep[x]->pipe[y])))
				== NULL)
			return (1);
		if (malloc_t_exec_redir(c, redir, x, y) == 1)
			return (1);
		y++;
	}
	return (0);
}

static int		len_sep(t_lchar *cmd)
{
	int		x;
	int		sep;

	x = 0;
	sep = 1;
	while (cmd[x].c != '\0')
	{
		if (cmd[x].type == _SEP)
			sep++;
		x++;
	}
	return (sep);
}

int				malloc_t_exec(t_lchar *cmd, t_exec *c)
{
	int		x;
	int		sep;
	int		pipe;

	x = 0;
	sep = len_sep(cmd);
	if ((c->sep = ft_memalloc(sizeof(*c->sep) * (sep + 1))) == NULL)
		return (1);
	while (x < sep)
	{
		pipe = len_pipe(cmd, x);
		if ((c->sep[x] = ft_memalloc(sizeof(*c->sep[x]))) == NULL)
			return (1);
		if (malloc_t_exec_pipe(cmd, c, pipe, x) == 1)
			return (1);
		x++;
	}
	return (0);
}
