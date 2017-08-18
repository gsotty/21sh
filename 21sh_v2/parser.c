/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 13:29:19 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/18 11:59:45 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./vingt_et_un_sh.h"

/*
** il me faut un char ** qui contien tous les cmd a exe dans le bonne ordre.
*/

static void	ft_exe_path(int len_cmd, int x, char **tab_cmd,
		t_struc_envp *struc_envp)
{
	int		len_path;
	int		nbr_path;
	char	*new_cmd;
	char	**path;

	path = ft_strsplit_space(find_var_env("PATH", struc_envp), ":");
	nbr_path = len_tab(path);
	while (x < nbr_path)
	{
		len_path = ft_strlen(path[x]);
		if ((new_cmd = ft_memalloc(sizeof(char) *
						(len_path + len_cmd + 2))) == NULL)
			return ;
		ft_memcpy(new_cmd, path[x], len_path);
		ft_memcpy(new_cmd + len_path, "/", 1);
		ft_memcpy(new_cmd + len_path + 1, tab_cmd[0], len_cmd);
		if (access(new_cmd, F_OK | X_OK) == 0)
			execve(new_cmd, tab_cmd, struc_envp->envp);
		free(new_cmd);
		x++;
	}
}

static void	ft_exe(char **tab_cmd, t_struc_envp *struc_envp)
{
	if (access(tab_cmd[0], F_OK | X_OK) == 0)
		execve(tab_cmd[0], tab_cmd, struc_envp->envp);
	else
		ft_exe_path(ft_strlen(tab_cmd[0]), 0, tab_cmd, struc_envp);
}

static void	exe_fork(int len_cmd, char **tab_cmd, t_struc_envp *struc_envp)
{
	pid_t	father;
	int		status;

	if (len_cmd == 0)
		return ;
	if ((father = fork()) == -1)
		ft_printf("error fork\n");
	if (father > 0)
	{
		signal(SIGINT, SIG_IGN);
		if ((wait(&status)) == -1)
			perror("wait");
		if (WIFSIGNALED(status) == 1)
			write(0, "\n", 1);
		return ;
	}
	if (father == 0)
	{
		ft_exe(tab_cmd, struc_envp);
		exit(0);
	}
}

int			parser(char *cmd, t_struc_envp *struc_envp)
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
	free(cmd);
	return (0);
}
