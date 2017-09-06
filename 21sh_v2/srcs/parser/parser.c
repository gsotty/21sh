/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 13:29:19 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/06 17:02:14 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

/*
** il me faut un char ** qui contien tous les cmd a exe dans le bonne ordre.
**
** token: pour le moemnt on a [||], [&&], [>>], [<<], [>], [<], [|], [;], [ ].
** il me manque: [n>], [>&n], [>& file_name], [n>>], [>|], [n>&n], [$>]
**
** ps: n = un monbre.
*/

static int		ft_while_parser_tri(t_lexer *s, t_token **begin_token,
		t_token **token, int *first_call)
{
	s->first_call_space = 1;
	while ((s->space = creat_token_space(s->redir->str,
					ft_strlen(s->redir->str),
					s->first_call_space)))
	{
		ft_printf("				space = \033[32m[%s], [%s]\n\033[0m",
				ft_print_type(s->space->type), s->space->str);
		s->first_call_space = 0;
		if (s->space->str[0] != '\0')
		{
			ft_printf("					good = \033[31m[%s], [%s]\n\033[0m",
					ft_print_type(s->space->type), s->space->str);
			if (*first_call == 0)
			{
				*begin_token = s->space;
				*token = *begin_token;
				*first_call = 1;
			}
			else
			{
				(*token)->next = s->space;
				*token = (*token)->next;
			}
		}
	}
	s->first_call_redir = 0;
	return (0);
}

static int		ft_while_parser_bis(t_lexer *s, t_token **begin_token,
		t_token **token, int *first_call)
{
	s->first_call_appredir = 1;
	while ((s->appredir = creat_token_appredir(s->pipe->str,
					ft_strlen(s->pipe->str), s->first_call_appredir)))
	{
		ft_printf("		appredir = \033[34m[%s], [%s]\n\033[0m",
				ft_print_type(s->appredir->type), s->appredir->str);
		s->first_call_redir = 1;
		while ((s->redir = creat_token_redir(s->appredir->str,
						ft_strlen(s->appredir->str), s->first_call_redir
						, s->appredir->type)))
		{
			ft_printf("			redir = \033[33m[%s], [%s]\n\033[0m",
					ft_print_type(s->redir->type), s->redir->str);
			ft_while_parser_tri(s, begin_token, token, first_call);
		}
		s->first_call_appredir = 0;
	}
	s->first_call_pipe = 0;
	return (0);
}

static int		ft_while_parser(t_lexer *s, t_token **begin_token,
		t_token **token, int *first_call)
{
	s->first_call_pipe = 1;
	while ((s->pipe = creat_token_pipe(s->sep->str,
					ft_strlen(s->sep->str), s->first_call_pipe,
					s->sep->type)) != NULL)
	{
		ft_printf("	pipe = \033[35m[%s], [%s]\n\033[0m",
				ft_print_type(s->pipe->type), s->pipe->str);
		ft_while_parser_bis(s, begin_token, token, first_call);
	}
	s->first_call_sep = 0;
	return (0);
}

int				print_tree(t_exec *c, t_nbr_lexer *nbr)
{
	int		x;
	int		y;
	int		z;

	x = 0;
	(void)nbr;
	while (c->sep[x] != NULL)
	{
		ft_printf("commande:\n");
		y = 0;
		while (c->sep[x]->cmd[y] != NULL)
		{
			ft_printf("	cmd:\n");
			ft_printf("		cmd_is:[%d]\n", c->sep[x]->cmd[y]->cmd_is);
			ft_printf("		fd_start:[%d]\n", c->sep[x]->cmd[y]->fd_start);
			ft_printf("		fd_end:[%d]\n", c->sep[x]->cmd[y]->fd_end);
			ft_printf("		argv:\n");
			ft_printf("			cmd:[%s]\n", c->sep[x]->cmd[y]->cmd.cmd);
			z = 0;
			while (c->sep[x]->cmd[y]->cmd.argv[z] != NULL)
			{
				ft_printf("			[%s]\n", c->sep[x]->cmd[y]->cmd.argv[z]);
				z++;
			}
			ft_printf("		file_name:[%s]\n", c->sep[x]->cmd[y]->file_name);
			y++;
		}
		x++;
	}
	return (0);
}

int				supp_space(t_token **begin_token, t_token **token,
		t_token **token_space)
{
	int		first_call;

	first_call = 0;
	while (*token_space != NULL)
	{
		if ((*token_space)->type == _FD && (*token_space)->next->type
				!= _RINT)
			(*token_space)->type = _WORD;
		if ((*token_space)->type != _SPACE)
		{
			ft_printf("[%s], [%s]\n", ft_print_type((*token_space)->type),
					(*token_space)->str);
			if (first_call == 0)
			{
				*begin_token = *token_space;
				*token = *begin_token;
				first_call = 1;
			}
			else
			{
				(*token)->next = *token_space;
				*token = (*token)->next;
			}
		}
		*token_space = (*token_space)->next;
	}
	return (0);
}

int				check_nbr(char *str, int len)
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

int				check_type_of_token(t_token *begin_token)
{
	int			x;
	int			len;
	int			is_rout;
	t_token		*token;

	x = 0;
	is_rout = 0;
	token = begin_token;
	while (token != NULL)
	{
		if (token->next != NULL)
		{
			len = (ft_strlen(token->str) - 1);
			if (ft_strstr(token->next->str, ">") != NULL &&
					(x = (check_nbr(token->str, len))) < len)
			{
				x++;
				token->next->fd = ft_atoi(token->str + x);
				token->str[x] = '\0';
			}
			if (ft_strstr(token->str, ">") != NULL)
			{
				is_rout = 1;
				token->type = _ROUT;
			}
			if (token->type == _WORD && is_rout == 1)
			{
				token->type = _FILE;
				is_rout = 0;
			}
			if (ft_strstr(token->str, "|") != NULL)
			{
				token->type = _PIPE;
			}
			if (ft_strstr(token->str, ";") != NULL)
			{
				token->type = _SEP;
			}
		}
		if (token->type != _SPACE)
		{
			if (token->type == _ROUT)
				ft_printf("sep = \033[31m[%s], [%d], [%s]\n\033[0m",
						ft_print_type(token->type), token->fd, token->str);
			else
				ft_printf("sep = \033[31m[%s],	[%s]\n\033[0m",
						ft_print_type(token->type), token->str);
		}
		token = token->next;
	}
	return (0);
}

int				parser(char *cmd, t_len_cmd *len, t_struc_envp *struc_envp)
{
	t_token		*begin_token;
	t_token		*token;
	t_token		*token_space;
	t_nbr_lexer	nbr;
	t_lexer		s;
	t_exec		c;
	int			first_call;

	(void)token;
	(void)nbr;
	ft_memset(&s, 0, sizeof(t_lexer));
	ft_memset(&c, 0, sizeof(t_exec));
	(void)struc_envp;
	token_space = NULL;
	if ((begin_token = ft_memalloc(sizeof(*begin_token))) == NULL)
		return (1);
	first_call = 0;
	s.first_call_sep = 1;
	while ((s.sep = creat_token_sep(cmd, len->len, s.first_call_sep)) != NULL)
	{
		ft_printf("sep = \033[36m[%s], [%s]\n\033[0m",
				ft_print_type(s.sep->type), s.sep->str);
		ft_while_parser(&s, &begin_token, &token_space, &first_call);
	}
	check_type_of_token(begin_token);
	//supp_space(&begin_token, &token, &token_space);
	//ft_memset(&nbr, 0, sizeof(nbr));
	//count_nbr_lexer(&nbr, begin_token);
	//creat_tab_cmd(&nbr, &c, begin_token);
	//print_tree(&c, &nbr);
	//	exe_tree(&c, &nbr, struc_envp);
	return (0);
}
