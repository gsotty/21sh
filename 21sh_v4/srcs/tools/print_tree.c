/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 17:20:45 by gsotty            #+#    #+#             */
/*   Updated: 2017/10/04 17:22:19 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static void		print_redir(t_redir **redir)
{
	int			x;

	x = 0;
	while (redir[x] != NULL)
	{
		ft_printf("\t\t\tredir = [%s]\n\t\t\t[%s]\n\t\t\t[%d]\n\t\t\t",
				redir[x]->file_name, ft_print_type(redir[x]->type),
				redir[x]->fd);
		ft_printf("[%d]\n\t\t\t[%s]\n\t\t\t[%d]\n\t\t\t[%d]\n",
				redir[x]->digit, redir[x]->heredoc, redir[x]->len_heredoc,
				redir[x]->option);
		x++;
	}
}

void			print_tree(t_exec *c)
{
	int			x;
	int			y;
	int			z;

	x = 0;
	ft_printf("exec = \n");
	while (c->sep[x] != NULL)
	{
		ft_printf("\tsep = \n");
		y = 0;
		while (c->sep[x]->pipe[y] != NULL)
		{
			ft_printf("\t\tpipe = \n");
			ft_printf("\t\t\tcmd = [%s]\n", c->sep[x]->pipe[y]->cmd.exec);
			z = 0;
			while (c->sep[x]->pipe[y]->cmd.argv[z] != NULL)
			{
				ft_printf("\t\t\tav = [%s]\n", c->sep[x]->pipe[y]->cmd.argv[z]);
				z++;
			}
			print_redir(c->sep[x]->pipe[y]->redir);
			y++;
		}
		x++;
	}
}
