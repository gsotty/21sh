/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 14:33:09 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/20 15:02:28 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./vingt_et_un_sh.h"

static int		ft_exe_path(int len_cmd, int x, char **tab_cmd,
		t_struc_envp *struc_envp)
{
	int			len_path;
	int			nbr_path;
	char		*new_cmd;
	char		**path;

	path = ft_strsplit_space(find_var_env("PATH", struc_envp), ":");
	nbr_path = len_tab(path);
	while (x < nbr_path)
	{
		len_path = ft_strlen(path[x]);
		if ((new_cmd = ft_memalloc(sizeof(char) *
						(len_path + len_cmd + 2))) == NULL)
			return (1);
		ft_memcpy(new_cmd, path[x], len_path);
		ft_memcpy(new_cmd + len_path, "/", 1);
		ft_memcpy(new_cmd + len_path + 1, tab_cmd[0], len_cmd);
		if (access(new_cmd, F_OK | X_OK) == 0)
		{
			execve(new_cmd, tab_cmd, struc_envp->envp);
			free(new_cmd);
			return (0);
		}
		free(new_cmd);
		x++;
	}
	return (1);
}

void			ft_exe(char **tab_cmd, t_struc_envp *struc_envp)
{
	int		len_cmd;

	len_cmd = ft_strlen(tab_cmd[0]);
	if (access(tab_cmd[0], F_OK | X_OK) == 0)
		execve(tab_cmd[0], tab_cmd, struc_envp->envp);
	else
	{
		if (ft_exe_path(len_cmd, 0, tab_cmd, struc_envp) == 1)
		{
			write(2, "21sh: command not found: ", 25);
			write(2, tab_cmd[0], len_cmd);
			write(2, "\n", 1);
		}
	}
}
