/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 18:01:22 by gsotty            #+#    #+#             */
/*   Updated: 2019/04/05 09:54:52 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"
#include "../../include/built_int.h"

#include <stdio.h>

int		which_pipefd(t_pipefd *pipefd, int type, int exit)
{
	return (pipefd->var == type ? pipefd->one[exit] : pipefd->two[exit]);
}

int		creat_pipefd(t_pipefd *pipefd, int type)
{
	if (pipe((pipefd->var == type ? pipefd->one : pipefd->two)) == -1)
	{
		write(2, "error pipe\n", 11);
		return (1);
	}
	return (0);
}

int		close_pipe_child(int count_pipe, int len, t_pipefd *pipefd)
{
	if (len > 1)
	{
		if (count_pipe == 0)
		{
			close(which_pipefd(pipefd, 0, 0));
			pipefd->var == 0 ? (pipefd->one[0] = -1) : (pipefd->two[0] = -1);
		}
		else if (count_pipe == (len - 1))
		{
			close(which_pipefd(pipefd, 1, 1));
			pipefd->var == 1 ? (pipefd->one[1] = -1) : (pipefd->two[1] = -1);
		}
		else
		{
			close(which_pipefd(pipefd, 1, 1));
			pipefd->var == 1 ? (pipefd->one[1] = -1) : (pipefd->two[1] = -1);
			close(which_pipefd(pipefd, 0, 0));
			pipefd->var == 0 ? (pipefd->one[0] = -1) : (pipefd->two[0] = -1);
		}
	}
	return (0);
}

int		close_pipe_father(int count_pipe, int len, t_pipefd *pipefd)
{
	if (len > 1)
	{
		if (count_pipe == 0)
		{
			close(which_pipefd(pipefd, 0, 1));
			pipefd->var == 0 ? (pipefd->one[1] = -1) : (pipefd->two[1] = -1);
		}
		else if (count_pipe == (len - 1))
		{
			close(which_pipefd(pipefd, 1, 0));
			pipefd->var == 1 ? (pipefd->one[0] = -1) : (pipefd->two[0] = -1);
		}
		else
		{
			close(which_pipefd(pipefd, 1, 0));
			pipefd->var == 1 ? (pipefd->one[0] = -1) : (pipefd->two[0] = -1);
			close(which_pipefd(pipefd, 0, 1));
			pipefd->var == 0 ? (pipefd->one[1] = -1) : (pipefd->two[1] = -1);
		}
	}
	return (0);
}

int		add_pipe(int count_pipe, int len, t_fdexec *fdexec, t_pipefd *pipefd)
{
	if (len > 1)
	{
		if (count_pipe == 0)
		{
			if (creat_pipefd(pipefd, 0) == 1)
				return (1);
			fdexec->fd_out = which_pipefd(pipefd, 0, 1);
		}
		else if (count_pipe == (len - 1))
		{
			fdexec->fd_in = which_pipefd(pipefd, 1, 0);
		}
		else
		{
			if (creat_pipefd(pipefd, 0) == 1)
				return (1);
			fdexec->fd_in = which_pipefd(pipefd, 1, 0);
			fdexec->fd_out = which_pipefd(pipefd, 0, 1);
		}
	}
	return (0);
}

static int		creat_here_document(t_typecmd *argv, char *exit, t_history *history)
{
	t_lchar		*tmp_buf;
	t_lchar		*new_buf;

	if ((argv->here_document = ft_memalloc(sizeof(t_lchar) + 1)) == NULL)
		return (1);
	while (1)
	{
		tmp_buf = while_main(2, history);
		if (ft_strmatch(exit, tmp_buf->c) == 1)
			break ;
		if (tmp_buf->len != -1)
		{
			if (argv->here_document->c != NULL)
			{
				new_buf = add_lchar(argv->here_document, tmp_buf);
				argv->here_document = new_buf;
			}
			else
				ft_lchardup(argv->here_document, tmp_buf, 0);
		}
		else
			return (1);
	}
	return (0);
}

int		ft_open_redir(char *file, t_typecmd *exec_struct, t_history *history)
{
	int		fd;

	fd = -2;
	printf("file open = [%s]\n", file);
	if (exec_struct->type_cmd == _RINT)
	{
		if ((fd = open(file, O_RDONLY)) == -1)
			write(2, "error: open\n", 12);
	}
	else if (exec_struct->type_cmd == _ROUT)
	{
		if ((fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR |
						S_IRGRP | S_IROTH)) == -1)
			write(2, "error: open\n", 12);
	}
	else if (exec_struct->type_cmd == _APPROUT)
	{
		if ((fd = open(file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR |
						S_IRGRP | S_IROTH)) == -1)
			write(2, "error: open\n", 12);
	}
	else if (exec_struct->type_cmd == _RRDWR)
	{
		if ((fd = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR |
						S_IRGRP | S_IROTH)) == -1)
			write(2, "error: open\n", 12);
	}
	else if (exec_struct->type_cmd == _HEREDOC)
	{
		if (creat_here_document(exec_struct, file, history) == 1)
			return (-2);
		return (-1);
	}
	else if (exec_struct->type_cmd == _DUPINT ||
			exec_struct->type_cmd == _DUPOUT)
		return (-1);
	return (fd);
}

t_builtin	builtin[] = {
	{"cd", cd},
	{"env", ft_env},
	{"setenv", ft_setenv},
	{"unsetenv", ft_unsetenv},
	{"echo", ft_echo},
	{NULL, NULL}
};

int		check_builtin(t_process *process, int count_process, t_fdexec *fdexec, t_pipefd *pipefd,
		char **argv, t_envp *my_envp)
{
	int		count;
	int		fd_dup;
	int		fd_close;
	int		fd_standard_in;
	int		fd_standard_out;

	count = 0;
	fd_dup = -1;
	fd_close = -1;
	fd_standard_in = -1;
	fd_standard_out = -1;
	while (builtin[count].exec != NULL)
	{
		if (ft_strmatch(argv[0], builtin[count].exec) == 1)
		{
			if (fdexec->fd_in != -1)
			{
				fd_standard_in = dup(fdexec->in);
				dup2(fdexec->fd_in, fdexec->in);
			}
			if (fdexec->fd_out != -1)
			{
				fd_standard_out = dup(fdexec->out);
				dup2(fdexec->fd_out, fdexec->out);
			}
			if (fdexec->close != -1)
			{
				fd_close = dup(fdexec->close);;
				close(fdexec->close);
			}
			if (fdexec->src != -1 && fdexec->dest != -1)
			{
				fd_dup = dup(fdexec->dest);;
				dup2(fdexec->src, fdexec->dest);
			}
			if (fdexec->here_document != NULL)
				close(pipefd->here_doc[1]);
			process[count_process].rep = builtin[count].founction(argv, my_envp);
			if (fd_standard_in != -1)
				dup2(fd_standard_in, fdexec->in);
			if (fd_standard_out != -1)
				dup2(fd_standard_out, fdexec->out);
			if (fd_close != -1)
				dup2(fd_close, fdexec->close);
			if (fd_dup != -1)
				dup2(fd_dup, fdexec->dest);
			return (1);
		}
		count++;
	}
	return (0);
}

int		exec_base(t_typecmd ****base, t_process *process, t_lenexec *lenexec,
		t_envp *my_envp, t_history *history)
{
	t_pipefd	*pipefd;

	t_fdexec	*fdexec;
	char		**argv;

	int			count_sep;
	int			count_process;
	int			count_pipe;
	int			count_cmd;

	int			argc;
	(void)lenexec;
//	int			rep;
//	int			status;

	count_sep = 0;
	count_process = 0;
	while (base[count_sep] != NULL)
	{
		count_pipe = 0;
		if ((pipefd = ft_memalloc(sizeof(t_pipefd))) == NULL)
			return (0);
		pipefd->one[0] = -1;
		pipefd->one[1] = -1;
		pipefd->two[0] = -1;
		pipefd->two[1] = -1;
		pipefd->here_doc[0] = -1;
		pipefd->here_doc[1] = -1;
		pipefd->var = 0;
		while (base[count_sep][count_pipe] != NULL)
		{
			if ((fdexec = ft_memalloc(sizeof(t_fdexec))) == NULL)
				return (0);
			fdexec->in = STDIN_FILENO;
			fdexec->out = STDOUT_FILENO;
			fdexec->fd_in = -1;
			fdexec->fd_out = -1;
			fdexec->close = -1;
			fdexec->src = -1;
			fdexec->dest = -1;
	///		if (add_pipe(count_pipe, lenexec->pipe[count_sep],
	//					fdexec, pipefd) == 1)
	//			return (1);
			count_cmd = 0;
			argc = 0;
			while (base[count_sep][count_pipe][count_cmd] != NULL)
			{
				if (base[count_sep][count_pipe][count_cmd]->type_cmd == _WORD)
					argc++;
				count_cmd++;
			}
			if (argc == 0)
				break ;
			if ((argv = ft_memalloc(sizeof(char *) * (argc + 1))) == NULL)
				return (1);
			count_cmd = 0;
			argc = 0;
			while (base[count_sep][count_pipe][count_cmd] != NULL)
			{
				if (base[count_sep][count_pipe][count_cmd]->r_fd == -1)
				{
					base[count_sep][count_pipe][count_cmd]->r_fd = ft_open_redir(
							base[count_sep][count_pipe][count_cmd]->file->c,
							base[count_sep][count_pipe][count_cmd], history);
				}
				if (base[count_sep][count_pipe][count_cmd]->type_cmd == _WORD)
				{
					if ((argv[argc] = ft_memalloc(sizeof(char) *
									base[count_sep][count_pipe][count_cmd]->len + 1)) == NULL)
						return (1);
					ft_memcpy(argv[argc],
							base[count_sep][count_pipe][count_cmd]->c,
							base[count_sep][count_pipe][count_cmd]->len);
					argv[argc][base[count_sep][count_pipe][count_cmd]->len] = '\0';
					argc++;
				}
				else if (base[count_sep][count_pipe][count_cmd]->type_cmd == 2)
				{
					fdexec->in = base[count_sep][count_pipe][count_cmd]->l_fd;
					fdexec->fd_in = base[count_sep][count_pipe][count_cmd]->r_fd;
				}
				else if (base[count_sep][count_pipe][count_cmd]->type_cmd >= 3 &&
						base[count_sep][count_pipe][count_cmd]->type_cmd <= 4)
				{
					fdexec->out = base[count_sep][count_pipe][count_cmd]->l_fd;
					fdexec->fd_out = base[count_sep][count_pipe][count_cmd]->r_fd;
				}
				else if (base[count_sep][count_pipe][count_cmd]->type_cmd == 5)
				{
					fdexec->in = base[count_sep][count_pipe][count_cmd]->l_fd;
					fdexec->fd_in = base[count_sep][count_pipe][count_cmd]->r_fd;
					fdexec->out = base[count_sep][count_pipe][count_cmd]->l_fd;
					fdexec->fd_out = base[count_sep][count_pipe][count_cmd]->r_fd;
				}
				else if (base[count_sep][count_pipe][count_cmd]->type_cmd == 6)
				{
					if ((fdexec->here_document = ft_memalloc(sizeof(t_lchar) + 1)) == NULL)
						return (1);
					ft_lchardup(fdexec->here_document, base[count_sep][count_pipe][count_cmd]->here_document, 0);
					if (pipe(pipefd->here_doc) == -1)
					{
						write(2, "error pipe\n", 11);
						return (1);
					}
					fdexec->in = base[count_sep][count_pipe][count_cmd]->l_fd;
					fdexec->fd_in = pipefd->here_doc[0];
				}
				else if (base[count_sep][count_pipe][count_cmd]->type_cmd == 7)
				{
					if (base[count_sep][count_pipe][count_cmd]->r_fd == -1)
					{
						if (base[count_sep][count_pipe][count_cmd]->file->len == 1
								&& base[count_sep][count_pipe][count_cmd]->file->c[0] == '-')
							fdexec->close = base[count_sep][count_pipe][count_cmd]->l_fd;
						else
						{
							fdexec->in = base[count_sep][count_pipe][count_cmd]->l_fd;
							fdexec->fd_in = open(base[count_sep][count_pipe][count_cmd]->file->c,
									O_RDONLY);
						}
					}
					else
					{
						fdexec->src = base[count_sep][count_pipe][count_cmd]->r_fd;
						fdexec->dest = base[count_sep][count_pipe][count_cmd]->l_fd;
					}
				}
				else if (base[count_sep][count_pipe][count_cmd]->type_cmd == 8)
				{
					if (base[count_sep][count_pipe][count_cmd]->r_fd == -1)
					{
						if (base[count_sep][count_pipe][count_cmd]->file->len == 1
								&& base[count_sep][count_pipe][count_cmd]->file->c[0] == '-')
							fdexec->close = base[count_sep][count_pipe][count_cmd]->l_fd;
						else
						{
							fdexec->out = base[count_sep][count_pipe][count_cmd]->l_fd;
							fdexec->fd_out = open(base[count_sep][count_pipe][count_cmd]->file->c,
									O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
						}
					}
					else
					{
						fdexec->src = base[count_sep][count_pipe][count_cmd]->r_fd;
						fdexec->dest = base[count_sep][count_pipe][count_cmd]->l_fd;
					}
				}
				count_cmd++;
			}
			argv[argc] = NULL;
/*
			fprintf(stderr, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
					which_pipefd(pipefd, 0, 0),
					which_pipefd(pipefd, 0, 1),
					which_pipefd(pipefd, 1, 0),
					which_pipefd(pipefd, 1, 1),
					pipefd->here_doc[0],
					pipefd->here_doc[1],
					fdexec->in,
					fdexec->fd_in,
					fdexec->out,
					fdexec->fd_out,
					fdexec->close,
					fdexec->src,
					fdexec->dest);
*/
			if (check_builtin(process, count_process, fdexec, pipefd, argv, my_envp) == 0)
			{
				pid_t		father;

				father = fork();
				if (father == 0)
				{
					signal(SIGINT, SIG_DFL);
//					if (close_pipe_child(count_pipe, lenexec->pipe[count_sep],
//								pipefd) == 1)
						return (1);
					if (fdexec->fd_in != -1)
						dup2(fdexec->fd_in, fdexec->in);
					if (fdexec->fd_out != -1)
						dup2(fdexec->fd_out, fdexec->out);
					if (fdexec->close != -1)
						close(fdexec->close);
					if (fdexec->here_document != NULL)
						close(pipefd->here_doc[1]);
					if (fdexec->src != -1 && fdexec->dest != -1)
						dup2(fdexec->src, fdexec->dest);
					exec_cmd(argc, argv, my_envp->envp);
					exit(0);
				}
				else if (father > 0)
				{
					process[count_process].id = father;
//					printf("father = [%d]\n", father);
					if (fdexec->here_document != NULL)
					{
						pid_t		father_redir;

						father_redir = fork();
						if (father_redir == 0)
						{
//							fprintf(stderr, "print here-doc = %d\n", pipefd->here_doc[1]);
							close(pipefd->here_doc[0]);
							pipefd->here_doc[0] = -1;
							write(pipefd->here_doc[1], fdexec->here_document->c,
									fdexec->here_document->len);
							write(pipefd->here_doc[1], "\n", 1);
							close(pipefd->here_doc[1]);
							pipefd->here_doc[1] = -1;
							exit(0);
						}
						else if (father_redir > 0)
						{
//							printf("father_redir = [%d]\n", father);
							close(pipefd->here_doc[1]);
							pipefd->here_doc[1] = -1;
						}
						else
						{
							write(2, "error fork\n", 11);
							return (1);
						}
					}
				}
				else
				{
					write(2, "error fork\n", 11);
					return (1);
				}
			}
	//		if (close_pipe_father(count_pipe, lenexec->pipe[count_sep],
	//					pipefd) == 1)
	//			return (1);
			count_cmd = 0;
			while (base[count_sep][count_pipe][count_cmd] != NULL)
			{
//				printf("fd = [%d], type = [%d]\n", base[count_sep][count_pipe][count_cmd]->r_fd,
//						base[count_sep][count_pipe][count_cmd]->type_cmd);
				if (base[count_sep][count_pipe][count_cmd]->type_cmd >= 2 &&
						base[count_sep][count_pipe][count_cmd]->type_cmd <= 5)
				{
					close(base[count_sep][count_pipe][count_cmd]->r_fd);
				}
				else if (base[count_sep][count_pipe][count_cmd]->type_cmd >= 7 &&
						base[count_sep][count_pipe][count_cmd]->type_cmd <= 8)
				{
					if (base[count_sep][count_pipe][count_cmd]->r_fd == -1)
					{
						if (base[count_sep][count_pipe][count_cmd]->file->len != 1
								|| base[count_sep][count_pipe][count_cmd]->file->c[0] != '-')
							close(base[count_sep][count_pipe][count_cmd]->r_fd);
					}
				}
				count_cmd++;
			}
			free(fdexec);
			pipefd->var = !pipefd->var;
			count_pipe++;
			count_process++;
		}
//		while ((rep = waitpid(-1, &status, 0)) > -1)
//		{
//			int		test_proc;
//
//			test_proc = 0;
//			while (test_proc < lenexec->nbr_process)
//			{
//				if (process[test_proc].id == rep)
//				{
//				//	printf("process = [%d]\n", process[test_proc].id);
//					process[test_proc].rep = WEXITSTATUS(status);
//				//	printf("	ret = [%d]\n", process[test_proc].rep);
//				}
//				test_proc++;
//			}
		//	printf("wait = [%d], rep = [%d]\n", rep, WEXITSTATUS(status));
//		}
		if (pipefd->here_doc[0] != -1)
		{
			close(pipefd->here_doc[0]);
			pipefd->here_doc[0] = -1;
		}
		if (pipefd->here_doc[1] != -1)
		{
			close(pipefd->here_doc[1]);
			pipefd->here_doc[1] = -1;
		}
		free(pipefd);
		count_sep++;
	}
	return (0);
}
