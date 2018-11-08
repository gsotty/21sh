/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_lchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 13:30:03 by gsotty            #+#    #+#             */
/*   Updated: 2017/10/04 14:04:50 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static void			pipe_sep(int type, t_define_lchar *struct_var, t_lchar *cmd)
{
	int		tmp_x;

	tmp_x = 0;
	cmd[struct_var->x].type = type;
	tmp_x = struct_var->x;
	ft_memset(struct_var, 0, sizeof(t_define_lchar));
	struct_var->x = tmp_x;
}

static void			and_or(int type, t_define_lchar *struct_var, t_lchar *cmd)
{
	cmd[struct_var->x].type = type;
	cmd[struct_var->x + 1].type = type;
	struct_var->is_redir = 0;
	struct_var->is_digit = 0;
}

int					define_lchar(t_lchar *cmd)
{
	t_define_lchar	var;

	ft_memset(&var, 0, sizeof(t_define_lchar));
	while (cmd[var.x].c != '\0' && cmd[var.x].c != '#')
	{
		if (cmd[var.x].type == 0)
		{
			if (cmd[var.x].c == ';')
				pipe_sep(_SEP, &var, cmd);
			else if (cmd[var.x].c == '&' && cmd[var.x + 1].c == '&')
				and_or(_AND, &var, cmd);
			else if (cmd[var.x].c == '|' && cmd[var.x + 1].c == '|')
				and_or(_OR, &var, cmd);
			else if (cmd[var.x].c == '|' && cmd[var.x].c != _OR)
				pipe_sep(_PIPE, &var, cmd);
			else if (cmd[var.x].c == '>' && cmd[var.x + 1].c == '>')
				approut_heredoc(_APPROUT, &var, cmd);
			else if (cmd[var.x].c == '<' && cmd[var.x + 1].c == '<')
				approut_heredoc(_HEREDOC, &var, cmd);
			else
				take_token(&var, cmd);
		}
		var.x++;
	}
	return (0);
}
