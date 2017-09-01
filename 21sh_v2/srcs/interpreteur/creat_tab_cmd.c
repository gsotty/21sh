/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_tab_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 15:37:14 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/01 12:57:18 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int		creat_tab_cmd(t_nbr_lexer *nbr, t_exec *c, t_token *begin_token)
{
	t_token		*token;
	int			x;
	int			nbr_argv;
	int			nbr_argv_2;
	int			is_pipe;
	int			nbr_pipe;

	token = begin_token;
	if ((c->sep = ft_memalloc(sizeof(*c->sep) * (nbr->_sep + 1))) == NULL)
		return (1);
	nbr_argv = 0;
	nbr_argv_2 = 0;
	is_pipe = 0;
	nbr_pipe = -1;
	if (token->str != NULL)
	{
		x = 0;
		if ((c->sep[x].pipe = ft_memalloc(sizeof(*c->sep[x].pipe) *
						(nbr->_pipe + 1))) == NULL)
			return (1);
		c->sep[x].cmd.cmd = NULL;
		while (token != NULL)
		{
			if (c->sep[x].cmd.cmd == NULL && is_pipe == 0)
			{
				c->sep[x].cmd.cmd = ft_strdup(token->str);
				c->sep[x].cmd.argv[nbr_argv] = ft_strdup(token->str);
				nbr_argv++;
			}
			else if (token->type == _WORD && is_pipe == 0)
			{
				if (nbr_argv < 1024)
				{
					c->sep[x].cmd.argv[nbr_argv] = ft_strdup(token->str);
					nbr_argv++;
				}
				else
					write(2, "putin tu a mis 2048 argv tu est debil\n", 38);
			}
			else if (token->type == _PIPE)
			{
				is_pipe = 1;
				nbr_pipe++;
				c->sep[x].pipe[nbr_pipe].cmd = NULL;
				c->sep[x].pipe[nbr_pipe + 1].cmd = NULL;
				nbr_argv_2 = 0;
			}
			else if (token->type == _SEP)
			{
				x++;
				is_pipe = 0;
				nbr_argv = 0;
				nbr_argv_2 = 0;
				nbr_pipe = -1;
				if ((c->sep[x].pipe = ft_memalloc(sizeof(*c->sep[x].pipe) *
								(nbr->_pipe + 1))) == NULL)
					return (1);
				c->sep[x].cmd.cmd = NULL;
			}
			else if (is_pipe == 1)
			{
				if (c->sep[x].pipe[nbr_pipe].cmd == NULL)
				{
					c->sep[x].pipe[nbr_pipe].cmd = ft_strdup(token->str);
					c->sep[x].pipe[nbr_pipe].argv[nbr_argv_2] =
							ft_strdup(token->str);
					nbr_argv_2++;
				}
				else if (token->type == _WORD)
				{
					if (nbr_argv_2 < 1024)
					{
						c->sep[x].pipe[nbr_pipe].argv[nbr_argv_2] =
							ft_strdup(token->str);
						nbr_argv_2++;
					}
					else
						write(2, "putin tu a mis 2048 argv tu est debil\n", 38);
				}
			}
			token = token->next;
		}
	}
	return (0);
}
