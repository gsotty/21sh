/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:37 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/19 16:59:18 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../vingt_et_un_sh.h"

void	print_tab(char **tableau)
{
	int		x;

	x = 0;
	while (tableau[x] != NULL)
	{
		ft_printf("[%s]\n", tableau[x]);
		x++;
	}
}

static int		init_main(char **envp, t_history *history)
{
	if (creat_envp(envp) == 1)
		return (1);
	if ((history->history = creat_history(history)) == NULL)
		return (1);
	return (0);
}

int			main(int argc, char **argv, char **envp)
{
	t_history		history;
	char			buffer[4];

	(void)argc;
	(void)argv;
	if (init_main(envp, &history) == 1)
		return (1);
	while (1)
	{
		if (init_termcaps() == 1)
			return (1);
		if (creat_buf(buffer, &history))
			break ;
		if (reset_termcaps() == 1)
			return (1);
	}
	if (reset_termcaps() == 1)
		return (1);
	if (export_history(&history) == 1)
		return (1);
	free_tab(g_envp);
	return (0);
}
