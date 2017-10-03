/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 16:15:46 by gsotty            #+#    #+#             */
/*   Updated: 2017/10/03 11:43:35 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

void	exec_ls(char **envp)
{
	char	*tab_1[5];

	tab_1[0] = "ls";
	tab_1[1] = "-l";
	tab_1[2] = ".";
	tab_1[3] = "qwer";
	tab_1[4] = NULL;
	execve("/bin/ls", tab_1, envp);
}

void	exec_cat(char **envp)
{
	char	*tab_1[3];

	tab_1[0] = "cat";
	tab_1[1] = "-e";
	tab_1[2] = NULL;
	execve("/bin/cat", tab_1, envp);
}

int		main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	int		pipefd_2[2];
	int		status;
	pid_t	rep;
	pid_t	father_ls;
	pid_t	father_cat;
	pid_t	father_cat_2;
	pid_t	father_cat_3;
	pid_t	tab_pid[4];

	if (pipe(pipefd) == -1 || pipe(pipefd_2) == -1)
	{
		write(2, "error\n", 6);
		return (1);
	}
	father_ls = fork();
	if (father_ls == 0)
	{
		close(pipefd_2[0]);
		close(pipefd_2[1]);
		close(pipefd[0]);
		dup2(pipefd[1], 2);
		dup2(pipefd[1], 1);
		exec_ls(envp);
		exit(0);
	}
	else if (father_ls > 0)
	{
		printf("creat_ls = [%d]\n", father_ls);
	}
	else
	{
		write(2, "error\n", 6);
		return (1);
	}
	father_cat = fork();
	if (father_cat == 0)
	{
		close(pipefd[1]);
		close(pipefd_2[0]);
		dup2(pipefd[0], 0);
		dup2(pipefd_2[1], 1);
		exec_cat(envp);
		exit(0);
	}
	else if (father_cat > 0)
	{
		printf("creat_cat = [%d]\n", father_cat);
	}
	else
	{
		write(2, "error\n", 6);
		return (1);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	if (pipe(pipefd) == -1)
	{
		write(2, "error\n", 6);
		return (1);
	}
	father_cat_2 = fork();
	if (father_cat_2 == 0)
	{
		close(pipefd[0]);
		close(pipefd_2[1]);
		dup2(pipefd_2[0], 0);
		dup2(pipefd[1], 1);
		exec_cat(envp);
		exit(0);
	}
	else if (father_cat_2 > 0)
	{
		printf("creat_cat_2 = [%d]\n", father_cat_2);
	}
	else
	{
		write(2, "error\n", 6);
		return (1);
	}
	father_cat_3 = fork();
	if (father_cat_3 == 0)
	{
		close(pipefd_2[0]);
		close(pipefd_2[1]);
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		exec_cat(envp);
		exit(0);
	}
	else if (father_cat_3 > 0)
	{
		printf("creat_cat_3 = [%d]\n", father_cat_2);
	}
	else
	{
		write(2, "error\n", 6);
		return (1);
	}

	close(pipefd[0]);
	close(pipefd[1]);
	close(pipefd_2[0]);
	close(pipefd_2[1]);
	tab_pid[0] = father_ls;
	tab_pid[1] = father_cat;
	tab_pid[2] = father_cat_2;
	tab_pid[3] = father_cat_3;
	while ((rep = wait(&status)) > -1)
	{
	/*	if (tab_pid[1] == rep)
			kill(father_ls, SIGQUIT);
		if (tab_pid[2] == rep)
			kill(father_cat, SIGQUIT);
		write(1, "\n", 1);
	*/	if (WIFSIGNALED(status) == 1)
			write(1, "\n", 1);
		printf("kill = [%d]\n", rep);
	}
	write(1, "\n", 1);
	return (0);
}
