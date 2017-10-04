/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 16:53:35 by gsotty            #+#    #+#             */
/*   Updated: 2017/10/04 17:54:23 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static int		ft_exe_path(char **path, int len_cmd, int x, t_cmd *cmd)
{
	int			len_path;
	int			nbr_path;
	char		*new_cmd;

	nbr_path = len_tab(path);
	while (x < nbr_path)
	{
		len_path = ft_strlen(path[x]);
		if (!(new_cmd = ft_memalloc(sizeof(char) * (len_path + len_cmd + 2))))
			return (1);
		ft_memcpy(new_cmd, path[x], len_path);
		ft_memcpy(new_cmd + len_path, "/", 1);
		ft_memcpy(new_cmd + len_path + 1, cmd->exec, len_cmd);
		if (access(new_cmd, F_OK | X_OK) == 0)
		{
			free(cmd->exec);
			cmd->exec = ft_strdup(new_cmd);
			free(new_cmd);
			execve(cmd->exec, cmd->argv, g_envp);
			return (0);
		}
		free(new_cmd);
		x++;
	}
	return (1);
}

void			exec_cmd(t_cmd cmd)
{
	int		len_cmd;

	len_cmd = ft_strlen(cmd.exec);
	if (access(cmd.exec, F_OK | X_OK) == 0)
		execve(cmd.exec, cmd.argv, g_envp);
	else
	{
		if (ft_exe_path(ft_strsplit_space(find_var_envp("PATH"), ":"),
					len_cmd, 0, &cmd) == 1)
		{
			write(2, "21sh: command not found: ", 25);
			write(2, cmd.exec, len_cmd);
			write(2, "\n", 1);
		}
	}
}
