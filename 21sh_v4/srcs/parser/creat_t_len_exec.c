/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_t_len_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 15:08:48 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/26 18:35:33 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int		creat_t_len_exec(t_lchar *cmd, t_len_exec *len_exec)
{
	int		x;

	x = 0;
	len_exec->sep = 1;
	len_exec->pipe = 1;
	len_exec->redir = 1;
	while (cmd[x].c != '\0')
	{
		if (cmd[x].type == _SEP)
			len_exec->sep++;
		else if (cmd[x].type == _PIPE)
			len_exec->pipe++;
		else if (cmd[x].type == _RINT || cmd[x].type == _ROUT ||
				cmd[x].type == _APPROUT || cmd[x].type == _HEREDOC ||
				cmd[x].type == _DUP_RINT || cmd[x].type == _DUP_ROUT ||
				cmd[x].type == _ROUTERR)
			len_exec->redir++;
		x++;
	}
	ft_printf("sep = [%d], pipe = [%d], redir = [%d]\n", len_exec->sep,
			len_exec->pipe, len_exec->redir);
	return (0);
}
