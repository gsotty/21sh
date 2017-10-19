/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 13:55:04 by gsotty            #+#    #+#             */
/*   Updated: 2017/10/04 14:10:56 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static void		add_word(t_define_lchar *struct_var, t_lchar *cmd)
{
	if (struct_var->is_cmd == 0)
	{
		if (struct_var->is_redir == 1)
			cmd[struct_var->x].type = _FILE_NAME;
		else
		{
			cmd[struct_var->x].type = _CMD;
			struct_var->cmd_is_enpli = 1;
		}
	}
	else if (struct_var->is_cmd == 1)
	{
		if (cmd[struct_var->x].type == 0)
		{
			if (struct_var->is_redir == 1)
				cmd[struct_var->x].type = _FILE_NAME;
			else
				cmd[struct_var->x].type = _ARGV;
		}
	}
}

static void		while_quote(int quote, t_define_lchar *struct_var,
		t_lchar *cmd)
{
	struct_var->x++;
	while (cmd[struct_var->x].c != quote && cmd[struct_var->x].c != '\0')
	{
		if (cmd[struct_var->x].c == '\\')
			struct_var->x++;
		add_word(struct_var, cmd);
		struct_var->x++;
	}
}

void			define_word(t_define_lchar *struct_var, t_lchar *cmd)
{
	if (cmd[struct_var->x].c == '\\')
		struct_var->x++;
	else if (cmd[struct_var->x].c == '\'')
		while_quote('\'', struct_var, cmd);
	else if (cmd[struct_var->x].c == '\"')
		while_quote('\"', struct_var, cmd);
	else
		add_word(struct_var, cmd);
}
