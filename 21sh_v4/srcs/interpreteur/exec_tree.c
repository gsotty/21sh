/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 16:47:53 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/29 17:59:41 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int		exec_tree(t_exec *c)
{
	int		sep;
	int		pipe;
	int		status;
	pid_t	father;

	sep = 0;
	while (c->sep[sep] != NULL)
	{
		pipe = 0;
		while (c->sep[sep]->pipe[pipe] != NULL)
		{
			father = fork();
			if (father == 0)
			{
				signal(SIGINT, SIG_DFL);
				exec_cmd(c->sep[sep]->pipe[pipe]->cmd);
				exit(0);
			}
			else if (father > 0)
			{
				signal(SIGINT, SIG_IGN);
				if ((wait(&status)) == -1)
					perror("wait");
				if (WIFSIGNALED(status) == 1)
					write(0, "\n", 1);
			}
			else
			{
				write(2, "error fork\n", 11);
			}
			pipe++;
		}
		sep++;
	}
	return (0);
}
