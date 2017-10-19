/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 16:47:53 by gsotty            #+#    #+#             */
/*   Updated: 2017/10/04 19:02:19 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

/*
**	if ((wait(&status)) == -1)
**		perror("wait");
**	if (WIFSIGNALED(status) == 1)
**		write(0, "\n", 1);
*/

static int	fork_base(int *pipefd_int, int *pipefd_out,
		t_cmd cmd, t_tab_pid_t *tab_pid)
{
	pid_t	father;

	father = fork();
	if (father == 0)
	{
		close_all(pipefd_int, pipefd_out);
		ft_printf("fd = [%d], [%d], [%d], [%d]\n", tab_pid->fd_int,
				tab_pid->fd_out, tab_pid->fd_to_int, tab_pid->fd_to_out);
		if (tab_pid->fd_to_int == -1 && tab_pid->fd_int != -1)
			dup2(tab_pid->fd_int, 0);
		else if (tab_pid->fd_to_int != -1 && tab_pid->fd_int != -1)
			dup2(tab_pid->fd_int, tab_pid->fd_to_int);
		if (tab_pid->fd_to_out == -1 && tab_pid->fd_out != -1)
			dup2(tab_pid->fd_out, 1);
		else if (tab_pid->fd_to_out != -1 && tab_pid->fd_out != -1)
			dup2(tab_pid->fd_out, tab_pid->fd_to_out);
		exec_cmd(cmd);
		exit(0);
	}
	else if (father > 0)
	{
		close_tow_fd(tab_pid->fd_int, tab_pid->fd_out);
		tab_pid->pid[tab_pid->len] = father;
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
		if (tab_pid->fd_to_int == -1 && tab_pid->fd_int != -1)
		{
			close(pipefd_int[0]);
			dup2(tab_pid->fd_int, 0);
		}
		else if (tab_pid->fd_to_int != -1 && tab_pid->fd_int != -1)
			dup2(tab_pid->fd_int, tab_pid->fd_to_int);
		if (tab_pid->fd_to_out == -1 && tab_pid->fd_out != -1)
			dup2(tab_pid->fd_out, 1);
		else if (tab_pid->fd_to_out != -1 && tab_pid->fd_out != -1)
			dup2(tab_pid->fd_out, tab_pid->fd_to_out);
		exec_cmd(cmd);
		close(pipefd_int[0]);
		exit(0);
	}
	else if (father > 0)
	{
		close_tow_fd(tab_pid->fd_int, tab_pid->fd_out);
		tab_pid->pid[tab_pid->len] = father;
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
		if (tab_pid->fd_to_int == -1 && tab_pid->fd_int != -1)
			dup2(tab_pid->fd_int, 0);
		else if (tab_pid->fd_to_int != -1 && tab_pid->fd_int != -1)
			dup2(tab_pid->fd_int, tab_pid->fd_to_int);
		if (tab_pid->fd_to_out == -1 && tab_pid->fd_out != -1)
		{
			close(pipefd_out[1]);
			dup2(tab_pid->fd_out, 1);
		}
		else if (tab_pid->fd_to_out != -1 && tab_pid->fd_out != -1)
			dup2(tab_pid->fd_out, tab_pid->fd_to_out);
		exec_cmd(cmd);
		close(pipefd_out[1]);
		exit(0);
	}
	else if (father > 0)
	{
		close_tow_fd(tab_pid->fd_int, tab_pid->fd_out);
		tab_pid->pid[tab_pid->len] = father;
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
		close_tow_fd(pipefd_int[1], pipefd_out[0]);
		dup2(pipefd_int[0], 0);
		dup2(pipefd_out[1], 1);
		if (tab_pid->fd_to_int == -1 && tab_pid->fd_int != -1)
		{
			close(pipefd_int[0]);
			dup2(tab_pid->fd_int, 0);
		}
		else if (tab_pid->fd_to_int != -1 && tab_pid->fd_int != -1)
			dup2(tab_pid->fd_int, tab_pid->fd_to_int);
		if (tab_pid->fd_to_out == -1 && tab_pid->fd_out != -1)
		{
			close(pipefd_out[1]);
			dup2(tab_pid->fd_out, 1);
		}
		else if (tab_pid->fd_to_out != -1 && tab_pid->fd_out != -1)
			dup2(tab_pid->fd_out, tab_pid->fd_to_out);
		exec_cmd(cmd);
		close_tow_fd(pipefd_int[0], pipefd_out[1]);
		exit(0);
	}
	else if (father > 0)
	{
		close_tow_fd(tab_pid->fd_int, tab_pid->fd_out);
		tab_pid->pid[tab_pid->len] = father;
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
	ft_memset(tab_pid, 0, sizeof(t_tab_pid_t));
	tab_pid->len = 0;
	if ((tab_pid->pid = ft_memalloc(sizeof(pid_t) * LEN_REMALLOC)) == NULL)
		return (1);
	tab_pid->len_malloc = LEN_REMALLOC;
	tab_pid->fd_int = -1;
	tab_pid->fd_out = -1;
	tab_pid->heredoc = -1;
	tab_pid->fd_to_int = -1;
	tab_pid->fd_to_out = -1;
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
			tmp_pid_t[x] = tab_pid->pid[x];
			x++;
		}
		free(tab_pid->pid);
		tab_pid->len_malloc += LEN_REMALLOC;
		if ((tab_pid->pid = ft_memalloc(sizeof(pid_t) *
						tab_pid->len_malloc)) == NULL)
			return (1);
		x = 0;
		while (x < tab_pid->len)
		{
			tab_pid->pid[x] = tmp_pid_t[x];
			x++;
		}
	}
	return (0);
}

int			exec_tree(t_exec *c)
{
	pid_t			rep;
	int				status;
	int				sep;
	int				f_pipe;
	int				redir;
	int				verif_int;
	int				rotaite_fd;
	int				pipefd_one[2];
	int				pipefd_tow[2];
	t_tab_pid_t		tab_pid;

	sep = 0;
	malloc_tab_pid_t(&tab_pid);
	while (c->sep[sep] != NULL)
	{
		f_pipe = 0;
		verif_int = 1;
		rotaite_fd = 0;
		if (pipe(pipefd_one) == -1 || pipe(pipefd_tow) == -1)
		{
			write(2, "error\n", 6);
			return (1);
		}
		while (c->sep[sep]->pipe[f_pipe] != NULL)
		{
			redir = 0;
			tab_pid.fd_int = -1;
			tab_pid.fd_out = -1;
			tab_pid.heredoc = -1;
			tab_pid.fd_to_int = -1;
			tab_pid.fd_to_out = -1;
			if (remalloc_pid_t(&tab_pid) == 1)
				return (1);
			while (c->sep[sep]->pipe[f_pipe]->redir[redir] != NULL)
			{
				if (c->sep[sep]->pipe[f_pipe]->redir[redir]->type == _RINT)
				{
					tab_pid.fd_int = open(c->sep[sep]->pipe[f_pipe]->redir[
							redir]->file_name, O_RDWR | O_CREAT,
							S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
					if (c->sep[sep]->pipe[f_pipe]->redir[redir]->fd != -1)
						tab_pid.fd_to_int =
							c->sep[sep]->pipe[f_pipe]->redir[redir]->fd;
				}
				else if (c->sep[sep]->pipe[f_pipe]->redir[redir]->type == _ROUT)
				{
					tab_pid.fd_out = open(c->sep[sep]->pipe[f_pipe]->redir[
							redir]->file_name, O_RDWR | O_CREAT | O_TRUNC,
							S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
					if (c->sep[sep]->pipe[f_pipe]->redir[redir]->fd != -1)
						tab_pid.fd_to_out =
							c->sep[sep]->pipe[f_pipe]->redir[redir]->fd;
				}
				else if (c->sep[sep]->pipe[f_pipe]->redir[redir]->type ==
						_APPROUT)
				{
					tab_pid.fd_out = open(c->sep[sep]->pipe[f_pipe]->redir[
							redir]->file_name, O_RDWR | O_CREAT | O_APPEND,
							S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
					if (c->sep[sep]->pipe[f_pipe]->redir[redir]->fd != -1)
						tab_pid.fd_to_out =
							c->sep[sep]->pipe[f_pipe]->redir[redir]->fd;
				}
				else if (c->sep[sep]->pipe[f_pipe]->redir[redir]->type ==
						_HEREDOC)
				{
					tab_pid.heredoc = 1;
					write(T_ROTAIT[1], c->sep[sep]->pipe[f_pipe]->redir[
							redir]->heredoc, c->sep[sep]->pipe[f_pipe]->redir[
							redir]->len_heredoc);
				}
				redir++;
			}
			if (c->sep[sep]->pipe[f_pipe + 1] != NULL && verif_int == 1)
			{
				verif_int = 0;
				if (fork_out(T_ROTAIT_INV, T_ROTAIT,
							c->sep[sep]->pipe[f_pipe]->cmd, &tab_pid) == 1)
					return (1);
			}
			else if (c->sep[sep]->pipe[f_pipe + 1] == NULL && verif_int == 0)
			{
				verif_int = 1;
				if (fork_int(T_ROTAIT, T_ROTAIT_INV,
							c->sep[sep]->pipe[f_pipe]->cmd, &tab_pid) == 1)
					return (1);
				close_all(pipefd_one, pipefd_tow);
			}
			else if (c->sep[sep]->pipe[f_pipe + 1] != NULL)
			{
				if (fork_int_and_out(T_ROTAIT, T_ROTAIT_INV,
							c->sep[sep]->pipe[f_pipe]->cmd, &tab_pid) == 1)
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
			else if (c->sep[sep]->pipe[f_pipe + 1] == NULL)
			{
				close_all(pipefd_one, pipefd_tow);
				fork_base(T_ROTAIT, T_ROTAIT_INV,
						c->sep[sep]->pipe[f_pipe]->cmd, &tab_pid);
			}
			else
			{
				return (1);
			}
			f_pipe++;
		}
		close_all(pipefd_one, pipefd_tow);
		while ((rep = waitpid(-1, &status, 0)) > -1)
		{
			ft_printf("wait = [%d], rep = [%d]\n", rep, WEXITSTATUS(status));
		}
		sep++;
	}
	write(1, "\n", 1);
	return (0);
}
