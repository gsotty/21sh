/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 13:29:19 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/13 14:23:42 by gsotty           ###   ########.fr       */
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

/*static int		ft_while_parser_tri(t_lexer *s, t_token **begin_token,
  t_token **token, int *first_call)
  {
  s->first_call_space = 1;
  while ((s->space = creat_token_space(s->redir->str,
  ft_strlen(s->redir->str),
  s->first_call_space, s->redir->type)))
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
 ft_strlen(s->pipe->str), s->first_call_appredir,
 s->pipe->type)))
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
	*/
int				print_tree(t_exec *c, t_nbr_lexer *nbr)
{
	int		x;
	int		y;
	int		z;
	int		i;

	x = 0;
	(void)nbr;
	while (c->sep[x] != NULL)
	{
		ft_printf("commande:\n");
		y = 0;
		while (c->sep[x]->pipe[y] != NULL)
		{
			ft_printf("	pipe:\n");
			ft_printf("		argv:\n");
			ft_printf("			cmd:[%s]\n", c->sep[x]->pipe[y]->cmd->exec);
			z = 0;
			while (c->sep[x]->pipe[y]->cmd->argv[z] != NULL)
			{
				ft_printf("			[%s]\n", c->sep[x]->pipe[y]->cmd->argv[z]);
				z++;
			}
			i = 0;
			while (c->sep[x]->pipe[y]->redir[i] != NULL)
			{
				ft_printf("			redir:[%s]\n", ft_print_type(
							c->sep[x]->pipe[y]->redir[i]->type));
				ft_printf("				fd:[%d]\n",
						c->sep[x]->pipe[y]->redir[i]->fd);
				ft_printf("				digit:[%d]\n",
						c->sep[x]->pipe[y]->redir[i]->digit);
				ft_printf("				tiret:[%d]\n",
						c->sep[x]->pipe[y]->redir[i]->option);
				ft_printf("				pipe:[%s]\n",
						c->sep[x]->pipe[y]->redir[i]->heredoc);
				ft_printf("				file_name:[%s]\n",
						c->sep[x]->pipe[y]->redir[i]->file_name);
				i++;
			}
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
/*
   int				check_type_of_token(t_token *begin_token)
   {
   int			x;
   int			is_rout;
   int			is_pipe;
   int			is_tiret;
   t_token		*token;

   x = 0;
   is_rout = 0;
   is_tiret = 0;
   token = begin_token;
   while (token != NULL)
   {
   if (token->type >= 3 && token->type <= 9)
   {
   if (token->type == _DUP_INPUT || token->type == _DUP_OUTPUT ||
   token->type == _HEREDOC)
   is_tiret = 1;
   else if (token->type == _ROUT)
   is_pipe = 1;
   is_rout = 1;
   }
   else if (token->type == _WORD && ft_strcmp(token->str, "|") == 0
   && is_pipe == 1)
   {
   token->type = _RPIPE;
   is_pipe = 0;
   }
   else if (token->type == _WORD && ft_strcmp(token->str, "-") == 0
   && is_tiret == 1)
   {
   token->type = _TIRET;
   is_tiret = 0;
   }
   else if (token->type == _WORD && is_rout == 1)
   {
   token->type = _FILE;
   is_rout = 0;
   is_tiret = 0;
   is_pipe = 0;
   }
   ft_printf("end = \033[31m[%s], [%s]\n\033[0m",
   ft_print_type(token->type), token->str);
   token = token->next;
   }
   return (0);
   }
   */

static int		define_lchar(t_lchar *cmd)
{
	int		x;
	int		y;
	int		is_cmd;
	int		is_redir;
	int		cmd_is_enpli;

	x = 0;
	y = 0;
	is_cmd = 0;
	is_redir = 0;
	cmd_is_enpli = 0;
	while (cmd[x].c != '\0')
	{
		if (cmd[x].c == '\\')
		{
			x++;
			if (is_cmd == 0)
			{
				if (is_redir == 1)
				{
					cmd[x].type = _FILE_NAME;
				}
				else
				{
					cmd[x].type = _CMD;
					cmd_is_enpli = 1;
				}
			}
			else if (is_cmd == 1)
			{
				if (cmd[x].type == 0)
				{
					if (is_redir == 1)
					{
						cmd[x].type = _FILE_NAME;
					}
					else
						cmd[x].type = _ARGV;
				}
			}
		}
		else if (cmd[x].c == '\'')
		{
			x++;
			while (cmd[x].c != '\'')
			{
				if (is_cmd == 0)
				{
					if (is_redir == 1)
					{
						cmd[x].type = _FILE_NAME;
					}
					else
					{
						cmd[x].type = _CMD;
						cmd_is_enpli = 1;
					}
				}
				else if (is_cmd == 1)
				{
					if (cmd[x].type == 0)
					{
						if (is_redir == 1)
						{
							cmd[x].type = _FILE_NAME;
						}
						else
							cmd[x].type = _ARGV;
					}
				}
				x++;
			}
		}
		else if (cmd[x].c == '\"')
		{
			x++;
			while (cmd[x].c != '\"')
			{
				if (is_cmd == 0)
				{
					if (is_redir == 1)
					{
						cmd[x].type = _FILE_NAME;
					}
					else
					{
						cmd[x].type = _CMD;
						cmd_is_enpli = 1;
					}
				}
				else if (is_cmd == 1)
				{
					if (cmd[x].type == 0)
					{
						if (is_redir == 1)
						{
							cmd[x].type = _FILE_NAME;
						}
						else
							cmd[x].type = _ARGV;
					}
				}
				x++;
			}
		}
		else if (cmd[x].c == ';')
		{
			cmd[x].type = _SEP;
			cmd_is_enpli = 0;
			is_redir = 0;
			is_cmd = 0;
		}
		else if (cmd[x].c == '&' && cmd[x + 1].c == '&')
		{
			cmd[x].type = _AND;
			cmd[x + 1].type = _AND;
			is_redir = 0;
		}
		else if (cmd[x].c == '|' && cmd[x + 1].c == '|')
		{
			cmd[x].type = _OR;
			cmd[x + 1].type = _OR;
			is_redir = 0;
		}
		else if (cmd[x].c == '|' && cmd[x].type != _OR)
		{
			cmd[x].type = _PIPE;
			cmd_is_enpli = 0;
			is_cmd = 0;
			is_redir = 0;
		}
		else if (cmd[x].c == '>' && cmd[x + 1].c == '>')
		{
			cmd[x].type = _APPROUT;
			cmd[x + 1].type = _APPROUT;
			is_redir = 1;
		}
		else if (cmd[x].c == '<' && cmd[x + 1].c == '<')
		{
			cmd[x].type = _HEREDOC;
			cmd[x + 1].type = _HEREDOC;
			is_redir = 1;
		}
		else if (cmd[x].c == '>' && cmd[x + 1].c == '&')
		{
			cmd[x].type = _DUP_ROUT;
			cmd[x + 1].type = _DUP_ROUT;
			is_redir = 1;
		}
		else if (cmd[x].c == '<' && cmd[x + 1].c == '&')
		{
			cmd[x].type = _DUP_RINT;
			cmd[x + 1].type = _DUP_RINT;
			is_redir = 1;
		}
		else if (cmd[x].c == '&' && cmd[x + 1].c == '>')
		{
			cmd[x].type = _ROUTERR;
			cmd[x + 1].type = _ROUTERR;
			is_redir = 1;
		}
		else if (cmd[x].c == '>')
		{
			cmd[x].type = _ROUT;
			is_redir = 1;
		}
		else if (cmd[x].c == '<')
		{
			cmd[x].type = _RINT;
			is_redir = 1;
		}
		else if (cmd[x].c == ' ' || cmd[x].c == '\t' || cmd[x].c == '\n')
		{
			cmd[x].type = _SPACE;
			if (cmd_is_enpli == 1)
				is_cmd = 1;
		}
		else if (cmd[x].c == '-' && (cmd[x + 1].c == ' ' ||
					cmd[x + 1].c == '\t' || cmd[x + 1].c == '\n'))
		{
			cmd[x].type = _TIRET;
		}
		else if ((cmd[x].type == _DUP_ROUT || cmd[x].type == _DUP_RINT)
				&& ft_isdigit(cmd[x + 1].c) == 1)
		{
			y = (x + 1);
			while (ft_isdigit(cmd[y].c) == 1)
				y++;
			x++;
			while (x < y)
			{
				cmd[x].type = _DIGIT;
				x++;
			}
			x--;
		}
		else if (ft_isdigit(cmd[x].c) == 1)
		{
			y = x;
			while (ft_isdigit(cmd[y].c) == 1)
				y++;
			if (cmd[y].c == '>' || cmd[y].c == '<')
			{
				while (x < y)
				{
					cmd[x].type = _FD;
					x++;
				}
				x--;
			}
			else
			{
				if (is_cmd == 0)
				{
					if (is_redir == 1)
					{
						cmd[x].type = _FILE_NAME;
					}
					else
					{
						cmd[x].type = _CMD;
						cmd_is_enpli = 1;
					}
				}
				else if (is_cmd == 1)
				{
					if (cmd[x].type == 0)
					{
						if (is_redir == 1)
						{
							cmd[x].type = _FILE_NAME;
						}
						else
							cmd[x].type = _ARGV;
					}
				}
			}
		}
		else if (is_cmd == 0)
		{
			if (is_redir == 1)
			{
				cmd[x].type = _FILE_NAME;
			}
			else
			{
				cmd[x].type = _CMD;
				cmd_is_enpli = 1;
			}
		}
		else if (is_cmd == 1)
		{
			if (cmd[x].type == 0)
			{
				if (is_redir == 1)
				{
					cmd[x].type = _FILE_NAME;
				}
				else
					cmd[x].type = _ARGV;
			}
		}
		x++;
	}
	return (0);
}

int				parser(t_lchar *cmd, t_len_cmd *len, t_struc_envp *struc_envp)
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
	(void)struc_envp;
	(void)len;
	ft_memset(&s, 0, sizeof(t_lexer));
	ft_memset(&c, 0, sizeof(t_exec));
	token_space = NULL;
	if ((begin_token = ft_memalloc(sizeof(*begin_token))) == NULL)
		return (1);
	first_call = 0;
	s.first_call_sep = 1;
	int	a=0;
	ft_printf("cmd 1 = \n");
	while (cmd[a].c != '\0')
	{
		ft_printf("[%c], [%s]\n", cmd[a].c, ft_print_type(cmd[a].type));
		a++;
	}
	define_lchar(cmd);
	a = 0;
	ft_printf("cmd 2 = \n");
	while (cmd[a].c != '\0')
	{
		ft_printf("[%c], [%s]\n", cmd[a].c, ft_print_type(cmd[a].type));
		a++;
	}
	/*
	   wm, hile ((s.sep = creat_token_sep(cmd, len->len, s.first_call_sep)) != NULL)
	   {
	   ft_printf("sep = \033[36m[%s], [%s]\n\033[0m",
	   ft_print_type(s.sep->type), s.sep->str);
	   ft_while_parser(&s, &begin_token, &token_space, &first_call);
	   }*/
	//check_type_of_token(begin_token);
	//supp_space(&begin_token, &token, &token_space);
	//ft_memset(&nbr, 0, sizeof(nbr));
	//count_nbr_lexer(&nbr, begin_token);
	//creat_tab_cmd(&nbr, &c, begin_token);
	//print_tree(&c, &nbr);
	//exe_tree(&c, &nbr, struc_envp);
	return (0);
}
