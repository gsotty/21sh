/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 16:47:53 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/30 17:32:55 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

/*
 **	if ((wait(&status)) == -1)
 **		perror("wait");
 **	if (WIFSIGNALED(status) == 1)
 **		write(0, "\n", 1);
 */

static int	fork_base(t_cmd cmd)
{
	pid_t	father;
	father = fork();

	if (father == 0)
	{
		exec_cmd(cmd);
		exit(0);
	}
	else if (father > 0)
	{
		ft_printf("creat_base = [%d]\n", father);
	}
	else
	{
		write(2, "error fork\n", 11);
		return (1);
	}
	return (0);
}

static char	*fork_out(t_cmd cmd, t_len_cmd *len)
{
	int		pipefd[2];
	char	buf;
	pid_t	father;
	char	*tmp_pipe;

	if (pipe(pipefd) == -1)
	{
		write(2, "error pipe\n", 11);
		return (NULL);
	}
	father = fork();
	if (father == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], 1) == -1)
		{
			write(2, "error dup2\n", 11);
			return (NULL);
		}
		exec_cmd(cmd);
		exit(0);
	}
	else if (father > 0)
	{
		ft_printf("creat_out = [%d]\n", father);
		if ((tmp_pipe = ft_memalloc(sizeof(char) * LEN_REMALLOC)) == NULL)
			return (NULL);
		len->len_malloc = LEN_REMALLOC;
		close(pipefd[1]);
		write(2, "111\n", 4);
		while (read(pipefd[0], &buf, 1) > 0)
		{
			tmp_pipe[len->len] = buf;
			len->len++;
			tmp_pipe = remalloc_cmd(len, tmp_pipe);
		}
		write(2, "333\n", 4);
		close(pipefd[0]);
	}
	else
	{
		close_tow_fd(pipefd[0], pipefd[1]);
		write(2, "error fork\n", 11);
		return (NULL);
	}
	return (tmp_pipe);
}

static int	fork_int(t_cmd cmd, char *tmp_pipe, t_len_cmd *len)
{
	int		pipefd[2];
	pid_t	father;

	if (pipe(pipefd) == -1)
	{
		write(2, "error pipe\n", 11);
		return (1);
	}
	father = fork();
	if (father == 0)
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], 0) == -1)
		{
			write(2, "error dup2\n", 11);
			return (1);
		}
		exec_cmd(cmd);
		exit(0);
	}
	else if (father > 0)
	{
		ft_printf("creat_int = [%d]\n", father);
		close(pipefd[0]);
		write(pipefd[1], tmp_pipe, len->len);
		close(pipefd[1]);
		wait(NULL);
	}
	else
	{
		close_tow_fd(pipefd[0], pipefd[1]);
		write(2, "error fork\n", 11);
		return (1);
	}
	return (0);
}

static char	*fork_int_and_out(t_cmd cmd, char *tmp_pipe, t_len_cmd *len)
{
	char	*new_tmp_pipe;
	int		pipefd_out[2];
	int		pipefd_int[2];
	char	buf;
	int		tmp_len;
	pid_t	father;

	tmp_len = len->len;
	ft_memset(len, 0, sizeof(t_len_cmd));
	if (pipe(pipefd_out) == -1 || pipe(pipefd_int) == -1)
	{
		write(2, "error pipe\n", 11);
		return (NULL);
	}
	father = fork();
	if (father == 0)
	{
		close_tow_fd(pipefd_out[0], pipefd_int[1]);
		if (dup2(pipefd_out[1], 1) == -1 || dup2(pipefd_int[0], 0) == -1)
		{
			write(2, "error dup2\n", 11);
			return (NULL);
		}
		exec_cmd(cmd);
		close_tow_fd(pipefd_out[1], pipefd_int[0]);
		exit(0);
	}
	else if (father > 0)
	{
		ft_printf("creat_out_and_int = [%d]\n", father);
		close_tow_fd(pipefd_int[0], pipefd_out[1]);
		write(pipefd_int[1], tmp_pipe, tmp_len);
		close(pipefd_int[1]);
		len->len = 0;
		len->len_malloc = LEN_REMALLOC;
		if ((new_tmp_pipe = ft_memalloc(sizeof(char) * LEN_REMALLOC)) == NULL)
			return (NULL);
		while ((read(pipefd_out[0], &buf, 1)) > 0)
		{
			new_tmp_pipe[len->len] = buf;
			len->len++;
			new_tmp_pipe = remalloc_cmd(len, new_tmp_pipe);
		}
		close(pipefd_out[0]);
	}
	else
	{
		close_all(pipefd_int, pipefd_out);
		write(2, "error fork\n", 11);
		return (NULL);
	}
	return (new_tmp_pipe);
}

//		signal(SIGINT, SIG_DFL);

int			exec_tree(t_exec *c)
{
	int			sep;
	int			pipe;
	char		*tmp_pipe;
	t_len_cmd	len;
	pid_t		father;

	sep = 0;
	tmp_pipe = NULL;
	while (c->sep[sep] != NULL)
	{
		pipe = 0;
		while (c->sep[sep]->pipe[pipe] != NULL)
		{
			father = fork();
			if (father == 0)
			{
				if (c->sep[sep]->pipe[pipe + 1] != NULL && tmp_pipe == NULL)
				{
					ft_memset(&len, 0, sizeof(t_len_cmd));
					if (!(tmp_pipe = fork_out(c->sep[sep]->pipe[pipe]->cmd,
									&len)))
						return (1);
				}
				else if (c->sep[sep]->pipe[pipe + 1] == NULL && tmp_pipe
						!= NULL)
				{
					if (fork_int(c->sep[sep]->pipe[pipe]->cmd, tmp_pipe, &len)
							== 1)
						return (1);
					ft_memset(&len, 0, sizeof(t_len_cmd));
					free(tmp_pipe);
				}
				else if (c->sep[sep]->pipe[pipe + 1] != NULL && tmp_pipe
						!= NULL)
				{
					if (!(tmp_pipe = fork_int_and_out(
									c->sep[sep]->pipe[pipe]->cmd,
									tmp_pipe, &len)))
						return (1);
				}
				else if (c->sep[sep]->pipe[pipe + 1] == NULL && tmp_pipe
						== NULL)
				{
					fork_base(c->sep[sep]->pipe[pipe]->cmd);
				}
				else
				{
					return (1);
				}
				exit(0);
			}
			else if (father > 0)
				ft_printf("creat_tree = [%d]\n", father);
			else
				return (1);
			pipe++;
		}
		sep++;
	}
	pid_t	rep;

	write(1, "111\n", 4);
	while ((rep = waitpid(-1, NULL, 0)) > -1)
	{
		ft_printf("kill = [%d]\n", rep);
		write(1, "222\n", 4);
	}
	return (0);
}
