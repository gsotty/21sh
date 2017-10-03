/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_lchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 13:30:03 by gsotty            #+#    #+#             */
/*   Updated: 2017/10/03 15:12:12 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static int			rep_nbr(int x, t_lchar *cmd)
{
	int		y;

	y = x - 1;
	while (cmd[y].type == _NBR && y > 0)
	{
		cmd[y].type = _FD;
		y--;
	}
	return (1);
}

static int			take_token(int x, t_define_lchar *struct_var, t_lchar *cmd)
{
	if (cmd[x].c == ';')
	{
		cmd[x].type = _SEP;
		ft_memset(struct_var, 0, sizeof(t_define_lchar));
	}
	else if (cmd[x].c == '&' && cmd[x + 1].c == '&')
	{
		cmd[x].type = _AND;
		cmd[x + 1].type = _AND;
		struct_var->is_redir = 0;
		struct_var->is_digit = 0;
	}
	else if (cmd[x].c == '|' && cmd[x + 1].c == '|')
	{
		cmd[x].type = _OR;
		cmd[x + 1].type = _OR;
		struct_var->is_redir = 0;
		struct_var->is_digit = 0;
	}
	else if (cmd[x].c == '|' && cmd[x].c != _OR)
	{
		cmd[x].type = _PIPE;
		ft_memset(struct_var, 0, sizeof(t_define_lchar));
	}
	else if (cmd[x].c == '>' && cmd[x + 1].c == '>')
	{
		cmd[x].type = _APPROUT;
		cmd[x + 1].type = _APPROUT;
		struct_var->is_redir = 1;
		struct_var->is_digit = 0;
		rep_nbr(x, cmd);
	}
	else if (cmd[x].c == '<' && cmd[x + 1].c == '<')
	{
		cmd[x].type = _HEREDOC;
		cmd[x + 1].type = _HEREDOC;
		struct_var->is_redir = 1;
		struct_var->is_digit = 0;
		rep_nbr(x, cmd);
	}
	else if (cmd[x].c == '<' && cmd[x + 1].c == '&')
	{
		cmd[x].type = _DUP_RINT;
		cmd[x + 1].type = _DUP_RINT;
		struct_var->is_tiret = 1;
		struct_var->is_digit = 1;
		struct_var->is_redir = 1;
		rep_nbr(x, cmd);
	}
	else if (cmd[x].c == '>' && cmd[x + 1].c == '&')
	{
		cmd[x].type = _DUP_ROUT;
		cmd[x + 1].type = _DUP_ROUT;
		struct_var->is_tiret = 1;
		struct_var->is_digit = 1;
		struct_var->is_redir = 1;
		rep_nbr(x, cmd);
	}
	else if (cmd[x].c == '&' && cmd[x + 1].c == '>')
	{
		cmd[x].type = _ROUTERR;
		cmd[x + 1].type = _ROUTERR;
		struct_var->is_redir = 1;
		struct_var->is_digit = 0;
	}
	else if (cmd[x].c == '>')
	{
		cmd[x].type = _ROUT;
		struct_var->is_redir = 1;
		struct_var->is_digit = 0;
		rep_nbr(x, cmd);
	}
	else if (cmd[x].c == '<')
	{
		cmd[x].type = _RINT;
		struct_var->is_redir = 1;
		struct_var->is_digit = 0;
		rep_nbr(x, cmd);
	}
	else if (cmd[x].c == ' ' || cmd[x].c == '\t' || cmd[x].c == '\n')
	{
		cmd[x].type = _SPACE;
		if (struct_var->cmd_is_enpli == 1)
			struct_var->is_cmd = 1;
	}
	else if (cmd[x].c == '-' && struct_var->is_tiret == 1)
	{
		cmd[x].type = _TIRET;
		struct_var->is_tiret = 0;
		struct_var->is_redir = 0;
		struct_var->is_digit = 0;
	}
	else if (ft_isdigit(cmd[x].c) == 1)
	{
		((struct_var->is_digit == 1) ? (cmd[x].type = _DIGIT) :
		 (cmd[x].type = _NBR));
	}
	return (0);
}

int					define_lchar(t_lchar *cmd)
{
	int				x;
	int				y;
	t_define_lchar	struct_var;

	x = 0;
	y = 0;
	ft_memset(&struct_var, 0, sizeof(t_define_lchar));
	while (cmd[x].c != '\0' && cmd[x].c != '#')
	{
		if (cmd[x].type == 0)
			take_token(x, &struct_var, cmd);
		x++;
	}
	return (0);
}
