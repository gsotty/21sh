/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_t_exec_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 14:26:49 by gsotty            #+#    #+#             */
/*   Updated: 2017/10/04 14:27:38 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int		malloc_t_exec_redir(t_exec *c, int redir, int x, int y)
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
