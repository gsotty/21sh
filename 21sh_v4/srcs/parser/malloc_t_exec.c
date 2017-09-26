/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_t_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 15:00:55 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/26 18:13:23 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static int		malloc_t_exec_redir(t_exec *c, t_len_exec *len_exec,
		int x, int y)
{
	int		z;

	z = 0;
	if ((c->sep[x]->pipe[y]->redir =
				ft_memalloc(sizeof(c->sep[x]->pipe[y]->redir) *
					(len_exec->redir + 1))) == NULL)
		return (1);
	while (z < len_exec->redir)
	{
		if ((c->sep[x]->pipe[y]->redir[z] =
					ft_memalloc(sizeof(c->sep[x]->pipe[y]->redir[z]))) == NULL)
			return (1);
		z++;
	}
	return (0);
}

static int		malloc_t_exec_pipe(t_exec *c, t_len_exec *len_exec, int x)
{
	int		y;

	y = 0;
	if ((c->sep[x]->pipe = ft_memalloc(sizeof(*c->sep[x]->pipe) *
					(len_exec->pipe + 1))) == NULL)
		return (1);
	while (y < len_exec->pipe)
	{
		if ((c->sep[x]->pipe[y] = ft_memalloc(sizeof(*c->sep[x]->pipe[y])))
				== NULL)
			return (1);
		if (malloc_t_exec_redir(c, len_exec, x, y) == 1)
			return (1);
		y++;
	}
	return (0);
}

int				malloc_t_exec(t_exec *c, t_len_exec *len_exec)
{
	int		x;

	x = 0;
	ft_printf("[%d]\n", len_exec->sep);
	if ((c->sep = ft_memalloc(sizeof(*c->sep) * (len_exec->sep + 1))) == NULL)
		return (1);
	while (x < len_exec->sep)
	{
		if ((c->sep[x] = ft_memalloc(sizeof(*c->sep[x]))) == NULL)
			return (1);
		if (malloc_t_exec_pipe(c, len_exec, x) == 1)
			return (1);
		x++;
	}
	return (0);
}
