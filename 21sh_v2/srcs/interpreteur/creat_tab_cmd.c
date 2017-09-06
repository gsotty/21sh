/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_tab_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 15:37:14 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/06 14:02:51 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int		malloc_sep(t_exec *c, t_nbr_lexer *nbr, int x)
{
	int		y;

	y = 0;
	if ((c->sep[x]->cmd = ft_memalloc(sizeof(*c->sep[x]->cmd) *
					(nbr->to_max + 1))) == NULL)
		return (1);
	while (y < nbr->to_max)
	{
		if ((c->sep[x]->cmd[y] = ft_memalloc(sizeof(*c->sep[x]->cmd[y])))
				== NULL)
			return (1);
		y++;
	}
	c->sep[x]->cmd[y] = NULL;
	return (0);
}

int		malloc_exec(t_exec *c, t_nbr_lexer *nbr)
{
	int		x;

	x = 0;
	if ((c->sep = ft_memalloc(sizeof(*c->sep) * (nbr->to_sep + 1))) == NULL)
		return (1);
	while (x < nbr->to_sep)
	{
		if ((c->sep[x] = ft_memalloc(sizeof(*c->sep[x]))) == NULL)
			return (1);
		malloc_sep(c, nbr, x);
		x++;
	}
	c->sep[x] = NULL;
	return (0);
}

int		creat_tab_cmd(t_nbr_lexer *nbr, t_exec *c, t_token *begin_token)
{
	int			x;
	int			y;
	int			nbr_argv;
	int			tmp_nbr;
	int			is_redi;
	t_token		*token;

	x = 0;
	y = 0;
	is_redi = 0;
	nbr_argv = 0;
	token = begin_token;
	malloc_exec(c, nbr);
	tmp_nbr = -1;
	while (token != NULL)
	{
		if (c->sep[x]->cmd[y]->cmd.cmd == NULL && token->type == _WORD)
		{
			c->sep[x]->cmd[y]->cmd.cmd = ft_strdup(token->str);
			c->sep[x]->cmd[y]->cmd.argv[nbr_argv] = ft_strdup(token->str);
			nbr_argv++;
		}
		else if (c->sep[x]->cmd[y]->cmd.cmd != NULL && token->type == _WORD)
		{
			c->sep[x]->cmd[y]->cmd.argv[nbr_argv] = ft_strdup(token->str);
			nbr_argv++;
		}
		if (token->type == _SEP)
		{
			nbr_argv = 0;
			y++;
		}
		else if (token->type == _PIPE)
		{
			nbr_argv = 0;
			y++;
		}
		else if (token->type == _ROUT)
		{
			token = token->next;
			if (c->sep[x]->cmd[y]->file_name != NULL)
				free(c->sep[x]->cmd[y]->file_name);
			c->sep[x]->cmd[y]->file_name = ft_strdup(token->str);
		//	y++;
		}
		else if (token->type == _RINT)
		{
			nbr_argv = 0;
			y++;
		}
/*		if (token->type == _SEP)
		{
			x++;
		}
		else if (token->type == _IO_NUMBER)
		{
			tmp_nbr = ft_atoi(token->str);
		}
		else if (token->type == _REDIR)
		{
			c->sep[x]->cmd[y]->cmd_is = _IS_ROUT;
			if (tmp_nbr == -1)
				c->sep[x]->cmd[y]->fd_start = 1;
			else
				c->sep[x]->cmd[y]->fd_start = tmp_nbr;
			c->sep[x]->cmd[y]->fd_end = 0;
			c->sep[x]->cmd[y]->cmd.cmd = NULL;
			c->sep[x]->cmd[y]->file_name = ft_strdup(token->next->str);
			y++;
		}
		else if (token->type == _LESS)
		{
			c->sep[x]->cmd[y]->cmd_is = _IS_RINT;
			c->sep[x]->cmd[y]->fd_start = 1;
			if (tmp_nbr == -1)
				c->sep[x]->cmd[y]->fd_end = 0;
			else
				c->sep[x]->cmd[y]->fd_end = tmp_nbr;
			c->sep[x]->cmd[y]->cmd.cmd = NULL;
			c->sep[x]->cmd[y]->file_name = ft_strdup(token->str);
			y++;
		}
		else if (token->type == _PIPE)
		{
			y++;
		}
*/		token = token->next;
	}
	return (0);
}
/*
int		creat_tab_cmd_2(t_nbr_lexer *nbr, t_exec *c, t_token *begin_token)
{
	t_token		*token;
	int			x;
	int			nbr_argv;
	int			nbr_argv_2;
	int			is_pipe;
	int			is_redi;
	int			nbr_pipe;

	token = begin_token;
	if ((c->sep = ft_memalloc(sizeof(*c->sep) * (nbr->_sep + 1))) == NULL)
		return (1);
	nbr_argv = 0;
	nbr_argv_2 = 0;
	is_pipe = 0;
	is_redi = 0;
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
					write(2, "putin tu a mis 1024 argv tu est debil\n", 38);
			}
			else if (token->type == _PIPE)
			{
				is_pipe = 1;
				nbr_pipe++;
				c->sep[x].pipe[nbr_pipe].cmd = NULL;
				c->sep[x].pipe[nbr_pipe + 1].cmd = NULL;
				nbr_argv_2 = 0;
			}
			else if (token->type == _IO_NUMBER && token->next->type == _REDIR)
			{
				ft_printf("111\n");
				c->sep[x].redi.fd = ft_atoi(token->str);
			}
			else if (token->type == _REDIR)
			{
				ft_printf("222\n");
				is_redi = 1;
			}
			else if (token->type == _SEP)
			{
				x++;
				is_pipe = 0;
				is_redi = 0;
				nbr_argv = 0;
				nbr_argv_2 = 0;
				nbr_pipe = -1;
				if ((c->sep[x].pipe = ft_memalloc(sizeof(*c->sep[x].pipe) *
								(nbr->_pipe + 1))) == NULL)
					return (1);
				c->sep[x].cmd.cmd = NULL;
			}
			else if (is_redi == 1)
			{
				ft_printf("333\n");
				if (token->type == _WORD)
				{
					c->sep[x].redi.file_name = ft_strdup(token->str);
				}
				is_redi = 0;
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
						write(2, "putin tu a mis 1024 argv tu est debil\n", 38);
				}
			}
			else
			{
				ft_printf("444\n");
			}
			token = token->next;
		}
	}
	return (0);
}*/
