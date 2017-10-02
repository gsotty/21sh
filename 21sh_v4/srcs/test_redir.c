/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 16:56:12 by gsotty            #+#    #+#             */
/*   Updated: 2017/10/02 11:04:40 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static int	execute_ls(char **envp)
{
	char	*tab1[3];

	tab1[0] = "ls";
	tab1[1] = "-l";
	tab1[2] = NULL;
	execve("/bin/ls", tab1, envp);
	return (1);
}

int			main(int argc, char **argv, char **envp)
{
	int		fd;
	pid_t	father;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
	{
		write(2, "error pipe\n", 11);
		return (1);
	}
	write(2, "111\n", 4);
	fd = open("test", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP |
		S_IROTH);
	father = fork();
	if (father == 0)
	{
		write(2, "222\n", 4);
		dup2(fd, 1);
		execute_ls(envp);
		exit(0);
	}
	else if (father > 0)
	{
		write(2, "333\n", 4);
		close(pipefd[1]);
	//	close(fd);
	}
	else
	{
		write(2, "444\n", 4);
		close(pipefd[0]);
		close(pipefd[1]);
		write(2, "error fork\n", 11);
		return (1);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	close(fd);
	wait(NULL);
	write(2, "444\n", 4);
	return (0);
}
