/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 12:58:33 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/01 16:37:42 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static char		*exe_pipe(int len, char *sorti, t_cmd *cmd,
		t_struc_envp *struc_envp)
{
	int		pipefd[2];
	int		pipefd_2[2];
	int		y;
	pid_t	father;
	pid_t	father_2;
	char	buf;
	char	*sorti_2;

	y = 0;
	(void)len;
	if ((sorti_2 = ft_memalloc(sizeof(char *) * 2048)) == NULL)
		return (NULL);
	if (pipe(pipefd) == -1)
	{
		write(2, "error\n", 6);
		return (NULL);
	}
	if (pipe(pipefd_2) == -1)
	{
		write(2, "error\n", 6);
		return (NULL);
	}
	father = fork();
	if (father == 0)
	{
		close(pipefd[1]);
		close(pipefd_2[0]);
		if (dup2(pipefd[0], 0) == -1)
			ft_printf("error\n");
		if (dup2(pipefd_2[1], 1) == -1)
			ft_printf("error\n");
		ft_exe(cmd, struc_envp);
		close(pipefd[0]);
		close(pipefd_2[1]);
		exit(0);
	}
	else if (father > 0)
	{
		father_2 = fork();
		if (father_2 == 0)
		{
			close(pipefd_2[1]);
			close(pipefd_2[0]);
			close(pipefd[0]);
			write(pipefd[1], sorti, ft_strlen(sorti));
			close(pipefd[1]);
			exit(0);
		}
		else if (father_2 > 0)
		{
			close(pipefd[0]);
			close(pipefd[1]);
			close(pipefd_2[1]);
			while (read(pipefd_2[0], &buf, 1) > 0)
				sorti_2[y++] = buf;
			sorti_2[y] = '\0';
			close(pipefd_2[0]);
			wait(NULL);
		}
		wait(NULL);
		//ft_printf("sorti = [%s]\n", sorti_2);
	}
	return (sorti_2);
}

int				exe_tree(t_exec *c, t_nbr_lexer *nbr, t_struc_envp *struc_envp)
{
	int		x;
	int		y;
	int		z;
	int		pipefd[2];
	char	buf;
	char	*sorti;
	pid_t	father;

	x = 0;
	y = 0;
	if ((sorti = ft_memalloc(sizeof(char *) * 2048)) == NULL)
		return (1);
	if (pipe(pipefd) == -1)
	{
		write(2, "error\n", 6);
		return (1);
	}
	while (x < nbr->_sep)
	{
		father = fork();
		if (father == 0)
		{
			if (nbr->_pipe > 0)
			{
				close(pipefd[0]);
				if (dup2(pipefd[1], 1) == -1)
					ft_printf("error\n");
				ft_exe(&c->sep[x].cmd, struc_envp);
				close(pipefd[1]);
				exit(0);
			}
			else
			{
				close(pipefd[0]);
				close(pipefd[1]);
				ft_exe(&c->sep[x].cmd, struc_envp);
				exit(0);
			}
		}
		else if (father > 0)
		{
			if (nbr->_pipe > 0)
			{
				close(pipefd[1]);
				while (read(pipefd[0], &buf, 1) > 0)
					sorti[y++] = buf;
				sorti[y] = '\0';
				close(pipefd[0]);
				wait(NULL);
				z = 0;
				while (c->sep[x].pipe[z].cmd != NULL)
				{
					sorti = exe_pipe(y, sorti, &c->sep[x].pipe[z], struc_envp);
					z++;
				}
			}
			else
			{
				close(pipefd[1]);
				close(pipefd[0]);
				wait(NULL);
			}
			ft_printf("sorti = [%s]\n", sorti);
			x++;
		}
	}
	return (0);
}
