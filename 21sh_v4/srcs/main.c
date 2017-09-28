/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:37 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/28 15:10:51 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../vingt_et_un_sh.h"

static int		init_main(char **envp, t_history *history)
{
	if (creat_envp(envp) == 1)
		return (1);
	if ((history->history = creat_history(history)) == NULL)
		return (1);
	return (0);
}

static int		exit_main(t_history *history)
{
	if (export_history(history) == 1)
		return (1);
	if (reset_termcaps() == 1)
		return (1);
	free_tab(g_envp);
	return (0);
}

int				main(int argc, char **argv, char **envp)
{
	char			buffer[4];
	t_lchar			*cmd;
	t_history		history;

	(void)argc;
	(void)argv;
	if (init_main(envp, &history) == 1)
		return (1);
	while (1)
	{
		if (init_termcaps() == 1)
			return (1);
		ft_signal();
		if ((cmd = creat_buf(0, LEN_REMAL_LI, buffer, &history)) == NULL)
			break ;
		if (add_history(&history, cmd, ft_strlen_lchar(cmd)) == 1)
			break ;
		if (reset_termcaps() == 1)
			return (1);
		if (cmd != NULL && cmd[0].c != '\0')
			if (parser(cmd, ft_strlen_lchar(cmd), &history) == 1)
				return (1);
	}
	return (exit_main(&history));
}
