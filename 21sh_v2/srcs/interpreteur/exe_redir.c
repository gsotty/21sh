/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 14:23:42 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/08 15:18:36 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"


static int		exe_redir_child(t_cmd_pipe *cmd, t_struc_envp *struc_envp)
{
	exit(0);
}

static int		exe_redir_father(t_cmd_pipe *cmd, t_struc_envp *struc_envp)
{
	wait(NULL);
	return (0);
}

static int		len_of_redir(t_cmd_redir **redir)
{
	int		x;

	x = 0;
	while (redir[x] != NULL)
		x++;
	return (x);
}

static int		filled_fd_file(int *fd_file, t_cmd_pipe *cmd)
{
	int		x;

	x = 0;
	while (cmd->redir[x] != NULL)
	{
		fd_file[x] = open(cmd->redir[x]->file_name, O_CREAT | O_RDWR);
		x++;
	}
	return (1);
}

int				exe_redir(t_cmd_pipe *cmd, t_struc_envp *struc_envp)
{
	int		*fd_file;
	int		len_redir;
	pid_t	father;

	len_redir = len_of_redir(cmd->redir);
	if ((fd_file = ft_memalloc(sizeof(int) * (len_redir + 1))) == NULL)
		return (1);
	filled_fd_file(fd_file, cmd);
	father = fork();
	if (father == 0)
	{
		exe_redir_child(cmd, struc_envp);
	}
	else if (father > 0)
	{
		exe_redir_father(cmd, struc_envp);
	}
	else
	{
		write(2, "ERROR\n", 6);
		return (1);
	}
	return (0);
}
