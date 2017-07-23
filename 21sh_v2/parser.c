/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 13:29:19 by gsotty            #+#    #+#             */
/*   Updated: 2017/07/23 15:38:42 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./vingt_et_un_sh.h"

/*
**
** il me faut un char ** qui contien tous les cmd a exe dans le bonne ordre.
**
*/

void	print_tab(char **tableau, int len_tab)
{
	int		x;

	x = 0;
	(void)len_tab;
	while (tableau[x] != NULL)
	{
		write(0, tableau[x], ft_strlen(tableau[x]));
		write(0, "\n", 1);
		x++;
	}
}

void	exe_fork(int len_cmd, char **tab_cmd, t_struc_envp *struc_envp)
{
	pid_t	father;

	(void)len_cmd;
	father = fork();
	if (father > 0)
	{
		wait(NULL);
		return ;
	}
	if (father == 0)
	{
		if (access(tab_cmd[0], F_OK | X_OK) == 0)
			execve(tab_cmd[0], tab_cmd, struc_envp->envp);
		exit(0);
	}
}

int		parser(char *cmd, t_struc_envp *struc_envp)
{
	char	**tab_cmd;
	int		len_cmd;

	(void)struc_envp;
	tab_cmd = ft_strsplit_space(cmd, " \t");
	len_cmd = len_tab(tab_cmd);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	exe_fork(len_cmd, tab_cmd, struc_envp);
	free_tab(tab_cmd, len_cmd);
	return (0);
}
