/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 16:47:53 by gsotty            #+#    #+#             */
/*   Updated: 2017/10/01 19:02:53 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

/*
**	if ((wait(&status)) == -1)
**		perror("wait");
**	if (WIFSIGNALED(status) == 1)
**		write(0, "\n", 1);
*/

static int	fork_base(t_cmd cmd, t_tab_pid_t *tab_pid)
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
		tab_pid->pid_t[tab_pid->len] = father;
		tab_pid->len++;
	}
	else
	{
		write(2, "error fork\n", 11);
		return (1);
	}
	return (0);
}

static int	fork_int(int *pipefd_int, int *pipefd_out, t_cmd cmd,
		t_tab_pid_t *tab_pid)
{
	pid_t	father;
	father = fork();

	if (father == 0)
	{
		close_tow_fd(pipefd_out[0], pipefd_out[1]);
		close(pipefd_int[1]);
		dup2(pipefd_int[0], 0);
		exec_cmd(cmd);
		close(pipefd_int[0]);
		exit(0);
	}
	else if (father > 0)
	{
		tab_pid->pid_t[tab_pid->len] = father;
		tab_pid->len++;
	}
	else
	{
		close_all(pipefd_int, pipefd_out);
		write(2, "error fork\n", 11);
		return (1);
	}
	return (0);
}

static int	fork_out(int *pipefd_int, int *pipefd_out, t_cmd cmd,
		t_tab_pid_t *tab_pid)
{
	pid_t	father;
	father = fork();

	if (father == 0)
	{
		close_tow_fd(pipefd_int[0], pipefd_int[1]);
		close(pipefd_out[0]);
		dup2(pipefd_out[1], 1);
		exec_cmd(cmd);
		close(pipefd_out[1]);
		exit(0);
	}
	else if (father > 0)
	{
		tab_pid->pid_t[tab_pid->len] = father;
		tab_pid->len++;
	}
	else
	{
		close_all(pipefd_int, pipefd_out);
		write(2, "error fork\n", 11);
		return (1);
	}
	return (0);
}

static int	fork_int_and_out(int *pipefd_int, int *pipefd_out, t_cmd cmd,
		t_tab_pid_t *tab_pid)
{
	pid_t	father;
	father = fork();

	if (father == 0)
	{
		close(pipefd_out[0]);
		close(pipefd_int[1]);
		dup2(pipefd_int[0], 0);
		dup2(pipefd_out[1], 1);
		exec_cmd(cmd);
		close(pipefd_out[1]);
		close(pipefd_int[0]);
		exit(0);
	}
	else if (father > 0)
	{
		tab_pid->pid_t[tab_pid->len] = father;
		tab_pid->len++;
	}
	else
	{
		close_all(pipefd_int, pipefd_out);
		write(2, "error fork\n", 11);
		return (1);
	}
	return (0);
}

static int	malloc_tab_pid_t(t_tab_pid_t *tab_pid)
{
	int		x;

	x = 0;
	ft_memset(tab_pid, 0, sizeof(t_tab_pid_t));
	tab_pid->len = 0;
	if ((tab_pid->pid_t = ft_memalloc(sizeof(pid_t) * LEN_REMALLOC)) == NULL)
		return (1);
	tab_pid->len_malloc = LEN_REMALLOC;
	return (0);
}

static int	remalloc_pid_t(t_tab_pid_t *tab_pid)
{
	int		x;
	pid_t	*tmp_pid_t;

	x = 0;
	if (tab_pid->len >= tab_pid->len_malloc)
	{
		if ((tmp_pid_t = ft_memalloc(sizeof(pid_t) * tab_pid->len)) == NULL)
			return (1);
		while (x < tab_pid->len)
		{
			tmp_pid_t[x] = tab_pid->pid_t[x];
			x++;
		}
		free(tab_pid->pid_t);
		tab_pid->len_malloc += LEN_REMALLOC;
		if ((tab_pid->pid_t = ft_memalloc(sizeof(pid_t) *
						tab_pid->len_malloc)) == NULL)
			return (1);
		x = 0;
		while (x < tab_pid->len)
		{
			tab_pid->pid_t[x] = tmp_pid_t[x];
			x++;
		}
	}
	return (0);
}

int			exec_tree(t_exec *c)
{
	int				fd;
	int				sep;
	int				_pipe;
	int				redir;
	int				verif_int;
	int				rotaite_fd;
	int				is_redir;
	int				pipefd_one[2];
	int				pipefd_tow[2];
	t_tab_pid_t		tab_pid;

	sep = 0;
	malloc_tab_pid_t(&tab_pid);
	while (c->sep[sep] != NULL)
	{
		_pipe = 0;
		verif_int = 1;
		rotaite_fd = 0;
		if (pipe(pipefd_one) == -1 || pipe(pipefd_tow) == -1)
		{
			write(2, "error\n", 6);
			return (1);
		}
		while (c->sep[sep]->pipe[_pipe] != NULL)
		{
			redir = 0;
			is_redir = 0;
			if (remalloc_pid_t(&tab_pid) == 1)
				return (1);
			while (c->sep[sep]->pipe[_pipe]->redir[redir] != NULL)
			{
				if (c->sep[sep]->pipe[_pipe]->redir[redir]->type == _RINT)
				{
					is_redir = 1;
					verif_int = 0;
					fd = open(c->sep[sep]->pipe[_pipe]->redir[redir]->file_name,
							O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP
							| S_IROTH);
				}
				if (c->sep[sep]->pipe[_pipe]->redir[redir]->type == _ROUT)
				{
					is_redir = 2;
					verif_int = 1;
					fd = open(c->sep[sep]->pipe[_pipe]->redir[redir]->file_name,
							O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP
							| S_IROTH);
				}
				redir++;
			}
			if (c->sep[sep]->pipe[_pipe + 1] != NULL && verif_int == 1 &&
					is_redir == 2)
			{
				verif_int = 0;
				if (fork_out(T_ROTAIT_INV, T_ROTAIT,
							c->sep[sep]->pipe[_pipe]->cmd, &tab_pid) == 1)
					return (1);
			}
			else if (c->sep[sep]->pipe[_pipe + 1] == NULL && verif_int == 0 &&
					is_redir == 1)
			{
				verif_int = 1;
				if (fork_int(T_ROTAIT, T_ROTAIT_INV,
							c->sep[sep]->pipe[_pipe]->cmd, &tab_pid) == 1)
					return (1);
				close_all(pipefd_one, pipefd_tow);
			}
			else if (c->sep[sep]->pipe[_pipe + 1] != NULL)
			{
				if (fork_int_and_out(T_ROTAIT, T_ROTAIT_INV,
							c->sep[sep]->pipe[_pipe]->cmd, &tab_pid) == 1)
					return (1);
				close_tow_fd(T_ROTAIT[0], T_ROTAIT[1]);
				if (pipe(T_ROTAIT) == -1)
				{
					if (rotaite_fd == 0)
					rotaite_fd = 1;
				}
				if (rotaite_fd == 0)
					rotaite_fd = 1;
				else
					rotaite_fd = 0;
			}
			else if (c->sep[sep]->pipe[_pipe + 1] == NULL)
			{
				close_all(pipefd_one, pipefd_tow);
				fork_base(c->sep[sep]->pipe[_pipe]->cmd, &tab_pid);
			}
			else
			{
				return (1);
			}
			_pipe++;
		}
		sep++;
	}
	pid_t	rep;

	close_all(pipefd_one, pipefd_tow);
	while ((rep = waitpid(-1, NULL, 0)) > -1)
	{
	}
	write(1, "\n", 1);
	return (0);
}
