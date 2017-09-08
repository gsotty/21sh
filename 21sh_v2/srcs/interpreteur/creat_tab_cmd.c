/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_tab_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 15:37:14 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/08 14:06:31 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int		malloc_redir(t_exec *c, t_nbr_lexer *nbr, int x, int y)
{
	int		z;

	z = 0;
	if ((c->sep[x]->cmd[y]->redir = ft_memalloc(
					sizeof(*c->sep[x]->cmd[y]->redir) *
					(nbr->to_redir + 1))) == NULL)
		return (1);
	while (z < nbr->to_redir)
	{
		if ((c->sep[x]->cmd[y]->redir[z] =
					ft_memalloc(sizeof(*c->sep[x]->cmd[y]->redir[z])))
				== NULL)
			return (1);
		z++;
	}
	c->sep[x]->cmd[y]->redir[z] = NULL;
	return (0);
}

int		malloc_sep(t_exec *c, t_nbr_lexer *nbr, int x)
{
	int		y;

	y = 0;
	if ((c->sep[x]->cmd = ft_memalloc(sizeof(*c->sep[x]->cmd) *
					(nbr->to_pipe + 2))) == NULL)
		return (1);
	while (y < (nbr->to_pipe + 1))
	{
		if ((c->sep[x]->cmd[y] = ft_memalloc(sizeof(*c->sep[x]->cmd[y])))
				== NULL)
			return (1);
		if (malloc_redir(c, nbr, x, y) == 1)
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
		if (malloc_sep(c, nbr, x) == 1)
			return (1);
		x++;
	}
	c->sep[x] = NULL;
	return (0);
}

int		check_nbr(char *str, int len)
{
	int		x;

	x = len;
	while (x >= 0)
	{
		if (ft_isdigit(str[x]) == 1)
			x--;
		else
			return (x);
	}
	return (x);
}

int		creat_tab_cmd(t_nbr_lexer *nbr, t_exec *c, t_token *begin_token)
{
	int			count_sep;
	int			count_pipe;
	int			count_redir;
	int			count_argv;
	int			first_word;
	int			is_redir;
	int			fd_is_define;
	int			len;
	int			x;
	t_token		*token;

	count_sep = 0;
	count_pipe = 0;
	count_redir = 0;
	count_argv = 0;
	first_word = 0;
	is_redir = 0;
	fd_is_define = 0;
	token = begin_token;
	if (malloc_exec(c, nbr) == 1)
		return (1);
	while (token != NULL)
	{
		if (token->next != NULL)
		{
			len = (ft_strlen(token->str) - 1);
			if ((token->next->type == _ROUT ||token->next->type == _RINT ||
						token->next->type == _DUP_OUTPUT ||
						token->next->type == _DUP_INPUT ||
						token->next->type == _APPROUT ||
						token->next->type == _HEREDOC)
					&& ((x = check_nbr(token->str, len)) < len))
			{
				x++;
				c->sep[count_sep]->cmd[count_pipe]->redir[count_redir]->fd =
					ft_atoi(token->str + x);
				token->str[x] = '\0';
				fd_is_define = 1;
			}
		}
		if (token->type == _WORD && first_word == 0 && token->str[0] != '\0')
		{
			c->sep[count_sep]->cmd[count_pipe]->cmd.cmd = ft_strdup(token->str);
			if ((count_argv + 1) < MAX_ARGV)
			{
				c->sep[count_sep]->cmd[count_pipe]->cmd.argv[count_argv] =
					ft_strdup(token->str);
				count_argv++;
			}
			else
			{
				write(2, "ERROR\n", 6);
			}
			first_word = 1;
		}
		else if (token->type == _WORD && first_word == 1 && token->str[0] != '\0')
		{
			if ((count_argv + 1) < MAX_ARGV)
			{
				c->sep[count_sep]->cmd[count_pipe]->cmd.argv[count_argv] =
					ft_strdup(token->str);
				count_argv++;
			}
			else
			{
				write(2, "ERROR\n", 6);
			}
		}
		else if (token->type >= 3 && token->type <= 9)
		{
			c->sep[count_sep]->cmd[count_pipe]->redir[count_redir]->
				type_of_redir = token->type;
			is_redir = 1;
		}
		else if (token->type == _RPIPE)
		{
			c->sep[count_sep]->cmd[count_pipe]->redir[count_redir]->pipe = 1;
		}
		else if (token->type == _TIRET)
		{
			c->sep[count_sep]->cmd[count_pipe]->redir[count_redir]->tiret = 1;
		}
		else if (token->type == _FILE)
		{
			c->sep[count_sep]->cmd[count_pipe]->redir[count_redir]->file_name
				= token->str;
			if (is_redir == 1)
			{
				is_redir = 0;
				if (fd_is_define == 0)
				{
					if (c->sep[count_sep]->cmd[count_pipe]->redir[count_redir]->
							type_of_redir == _DUP_INPUT ||
							c->sep[count_sep]->cmd[count_pipe]->
							redir[count_redir]->type_of_redir == _HEREDOC ||
							c->sep[count_sep]->cmd[count_pipe]->
							redir[count_redir]->type_of_redir == _RINT)
					{
						c->sep[count_sep]->cmd[count_pipe]->
							redir[count_redir]->fd = 1;
					}
					if (c->sep[count_sep]->cmd[count_pipe]->redir[count_redir]->
							type_of_redir == _DUP_OUTPUT ||
							c->sep[count_sep]->cmd[count_pipe]->
							redir[count_redir]->type_of_redir == _APPROUT ||
							c->sep[count_sep]->cmd[count_pipe]->
							redir[count_redir]->type_of_redir == _ROUT)
					{
						c->sep[count_sep]->cmd[count_pipe]->
							redir[count_redir]->fd = 0;
					}
				}
				fd_is_define = 0;
				count_redir++;
			}
		}
		if (token->type == _PIPE)
		{
			count_pipe++;
			count_redir = 0;
			count_argv = 0;
			first_word = 0;
			is_redir = 0;
			fd_is_define = 0;
		}
		if (token->type == _SEP)
		{
			count_sep++;
			count_pipe = 0;
			count_redir = 0;
			count_argv = 0;
			first_word = 0;
			is_redir = 0;
			fd_is_define = 0;
		}
		token = token->next;
	}
	return (0);
}
