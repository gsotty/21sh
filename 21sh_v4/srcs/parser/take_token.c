/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 12:14:57 by gsotty            #+#    #+#             */
/*   Updated: 2017/10/04 14:07:36 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static void		dup_rint_dup_rout(int type, t_define_lchar *struct_var,
		t_lchar *cmd)
{
	cmd[struct_var->x].type = type;
	cmd[struct_var->x + 1].type = type;
	struct_var->is_tiret = 1;
	struct_var->is_digit = 1;
	struct_var->is_redir = 1;
	rep_nbr(struct_var->x, cmd);
}

static void		rint_rout(int type, t_define_lchar *struct_var,
		t_lchar *cmd)
{
	cmd[struct_var->x].type = type;
	struct_var->is_redir = 1;
	struct_var->is_digit = 0;
	rep_nbr(struct_var->x, cmd);
}

static void		space(int type, t_define_lchar *struct_var, t_lchar *cmd)
{
	cmd[struct_var->x].type = type;
	if (struct_var->cmd_is_enpli == 1)
		struct_var->is_cmd = 1;
}

static void		tiret(int type, t_define_lchar *struct_var, t_lchar *cmd)
{
	cmd[struct_var->x].type = type;
	struct_var->is_tiret = 0;
	struct_var->is_redir = 0;
	struct_var->is_digit = 0;
}

void			take_token(t_define_lchar *var, t_lchar *cmd)
{
	if (cmd[var->x].c == '<' && cmd[var->x + 1].c == '&')
		dup_rint_dup_rout(_DUP_RINT, var, cmd);
	if (cmd[var->x].c == '>' && cmd[var->x + 1].c == '&')
		dup_rint_dup_rout(_DUP_ROUT, var, cmd);
	else if (cmd[var->x].c == '&' && cmd[var->x + 1].c == '>')
		approut_heredoc(_ROUTERR, var, cmd);
	else if (cmd[var->x].c == '>')
		rint_rout(_ROUT, var, cmd);
	else if (cmd[var->x].c == '<')
		rint_rout(_RINT, var, cmd);
	else if (cmd[var->x].c == ' ' || cmd[var->x].c == '\t' ||
			cmd[var->x].c == '\n')
		space(_SPACE, var, cmd);
	else if (cmd[var->x].c == '-' && var->is_tiret == 1)
		tiret(_TIRET, var, cmd);
	else if (ft_isdigit(cmd[var->x].c) == 1)
		((var->is_digit == 1) ? (cmd[var->x].type = _DIGIT) :
			(cmd[var->x].type = _NBR));
	else
		define_word(var, cmd);
}
