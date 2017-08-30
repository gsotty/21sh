/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 16:27:48 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/30 16:33:11 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "./../vingt_et_un_sh.h"

	int
main(int argc, char *argv[], char **envp)
{
	int		pipefd[2];
	pid_t	cpid;
	char	buf;
	char	*tab_1[3];
	char	*tab_cat[4];
	char	cmd[2048];
	int		x;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (cpid == 0)
	{
		tab_1[0] = "/bin/ls";
		tab_1[1] = "-l";
		tab_1[2] = NULL;
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		if (execve(tab_1[0], tab_1, envp) != -1)
		{
			printf("error\n");
			return (0);
		}
		close(pipefd[1]);
		_exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipefd[1]);
		x = 0;
		while (read(pipefd[0], &buf, 1) > 0)
		{
			printf("%c", buf);
			cmd[x] = buf;
			x++;
		}
		cmd[x] = '\0';
		printf("%s", cmd);
		close(pipefd[0]);
		wait(NULL);
		tab_cat[0] = "/bin/cat";
		tab_cat[1] = "-e";
		tab_cat[2] = NULL;
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		cpid = fork();
		if (cpid == 0)
		{
			close(pipefd[1]);
			dup2(pipefd[0], 0);
			if (execve(tab_cat[0], tab_cat, envp) != -1)
			{
				printf("error\n");
				return (0);
			}
			close(pipefd[0]);
			_exit(EXIT_SUCCESS);
		}
		else
		{
			close(pipefd[0]);
			write(pipefd[1], cmd, strlen(cmd));
			close(pipefd[1]);
			wait(NULL);
		}
		exit(EXIT_SUCCESS);
	}
}
