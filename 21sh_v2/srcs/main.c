/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 10:53:29 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/24 15:31:25 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../vingt_et_un_sh.h"

static int		main_ini_envp(int argc, char **argv, char **envp,
		t_struc_envp *struc_envp)
{
	(void)argc;
	(void)argv;
	ft_memset(struc_envp, 0, sizeof(struc_envp));
	struc_envp->len = len_tab(envp);
	if ((struc_envp->envp = creat_envp(envp, struc_envp->len)) == NULL)
		return (1);
	return (0);
}

static int		main_ini_history(t_history *history)
{
	ft_memset(history, 0, sizeof(history));
	if ((history->history = creat_history(history)) == NULL)
		return (1);
	return (0);
}

static int		main_loop(char *buffer, t_history *history,
		t_struc_envp *struc_envp, char *cmd)
{
	t_len_cmd		len;

	ft_memset(&len, 0, sizeof(len));
	if (prepare_term() != 0)
		return (1);
	if ((cmd = creat_buf(buffer, &len, history)) == NULL)
		return (1);
	if (reset_term() != 0)
		return (1);
	if (parser(cmd, &len, struc_envp) == 1)
		return (1);
	return (0);
}

int				main(int argc, char **argv, char **envp)
{
	t_struc_envp			struc_envp;
	t_history				history;
	char					buffer[4];

	if ((main_ini_envp(argc, argv, envp, &struc_envp) == 1) ||
			main_ini_history(&history) == 1)
		return (1);
	while (1)
		if (main_loop(buffer, &history, &struc_envp, NULL) == 1)
			break ;
	export_history(&history);
	free_tab(struc_envp.envp, struc_envp.len);
	if (reset_term() != 0)
		return (1);
	return (0);
}
