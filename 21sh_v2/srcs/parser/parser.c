/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 13:29:19 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/01 13:52:13 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

/*
 ** il me faut un char ** qui contien tous les cmd a exe dans le bonne ordre.
 */

static int		ft_while_parser_tri(t_lexer *s, t_token **begin_token,
		t_token **token, int *first_call)
{
	s->first_call_space = 1;
	while ((s->space = creat_token_space(s->gr_le->str,
					ft_strlen(s->gr_le->str),
					s->first_call_space)))
	{
		//	ft_printf("space = [%s] [%s]\n",
		//			ft_print_type(s->space->type), s->space->str);
		s->first_call_space = 0;
		if (s->space->type != _SPACE)
		{
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
	s->first_call_gr_le = 0;
	return (0);
}

static int		ft_while_parser_bis(t_lexer *s, t_token **begin_token,
		t_token **token, int *first_call)
{
	s->first_call_dg_dl = 1;
	while ((s->dg_dl = creat_token_dg_dl(s->pipe->str,
					ft_strlen(s->pipe->str), s->first_call_dg_dl)))
	{
		s->first_call_gr_le = 1;
		while ((s->gr_le = creat_token_gr_le(s->dg_dl->str,
						ft_strlen(s->dg_dl->str), s->first_call_gr_le
						, s->dg_dl->type)))
		{
			ft_while_parser_tri(s, begin_token, token, first_call);
		}
		s->first_call_dg_dl = 0;
	}
	s->first_call_pipe = 0;
	return (0);
}

static int		ft_while_parser(t_lexer *s, t_token **begin_token,
		t_token **token, int *first_call)
{
	s->first_call_and_or = 1;
	while ((s->and_or = creat_token_and_or(s->sep->str, ft_strlen(s->sep->str),
					s->first_call_and_or)) != NULL)
	{
		s->first_call_pipe = 1;
		while ((s->pipe = creat_token_pipe(s->and_or->str,
						ft_strlen(s->and_or->str), s->first_call_pipe,
						s->and_or->type)) != NULL)
		{
			ft_while_parser_bis(s, begin_token, token, first_call);
		}
		s->first_call_and_or = 0;
	}
	s->first_call_sep = 0;
	return (0);
}

int				print_tree(t_exec *c, t_nbr_lexer *nbr)
{
	int    a = 0;
	int    b = 0;
	int    d = 0;
	int    e = 0;
	while (a < nbr->_sep)
	{
		ft_printf("commande:\n");
		if (c->sep[a].cmd.cmd != NULL)
		{
			b = 0;
			ft_printf("		cmd:[%s]\n", c->sep[a].cmd.cmd);
			while (c->sep[a].cmd.argv[b] != NULL)
			{
				ft_printf("		argv:[%s]\n", c->sep[a].cmd.argv[b]);
				b++;
			}
			e = 0;
			while (e < nbr->_pipe)
			{
				if (c->sep[a].pipe[e].cmd != NULL)
				{
					ft_printf("		pipe:\n");
					ft_printf("			cmd:[%s]\n",
							c->sep[a].pipe[e].cmd);
					d = 0;
					while (c->sep[a].pipe[e].argv[d] != NULL)
					{
						ft_printf("			argv:[%s]\n",
								c->sep[a].pipe[e].argv[d]);
						d++;
					}
				}
				e++;
			}
		}
		a++;
	}
	return (0);
}

int				parser(char *cmd, t_len_cmd *len, t_struc_envp *struc_envp)
{
	t_token		*begin_token;
	t_token		*token;
	t_nbr_lexer	nbr;
	t_lexer		s;
	t_exec		c;
	int			first_call;

	ft_memset(&s, 0, sizeof(t_lexer));
	ft_memset(&c, 0, sizeof(t_exec));
	(void)struc_envp;
	token = NULL;
	if ((begin_token = ft_memalloc(sizeof(*begin_token))) == NULL)
		return (1);
	first_call = 0;
	s.first_call_sep = 1;
	while ((s.sep = creat_token_sep(cmd, len->len, s.first_call_sep)) != NULL)
	{
		ft_while_parser(&s, &begin_token, &token, &first_call);
	}
	ft_memset(&nbr, 0, sizeof(nbr));
	count_nbr_lexer(&nbr, begin_token);
	creat_tab_cmd(&nbr, &c, begin_token);
	//print_tree(&c, &nbr);
	exe_tree(&c, &nbr, struc_envp);
	return (0);
}
