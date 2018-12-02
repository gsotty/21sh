#include "../../include/parser.h"

static void	init_struct_redir(t_redirections *redir)
{
	redir->type = -1;
	redir->fd_int = -1;
	redir->file_int = NULL;
	redir->fd_out = -1;
	redir->file_out = NULL;
	redir->len_heredoc = 0;
	redir->heredoc = NULL;
}

static int	is_a_file_name(t_lchar *buf, int *x, int end_redir,
		t_redirections *redir)
{
	int	start_file;

	start_file = *x;
	while (buf->type[*x] == _FILE_NAME)
	{
		*x = *x + 1;
		if (end_redir < *x || buf->type[*x] != _FILE_NAME)
		{
			if (redir->type == _ROUT || redir->type == _APPROUT)
			{
				redir->fd_int = 0;
				redir->fd_out = 1;
				if ((redir->file_out = ft_memalloc(sizeof(char) *
								((*x - start_file) + 1))) == NULL)
					return (1);
				ft_memcpy(redir->file_out, buf->c + start_file,
						*x - start_file);
			}
			else if (redir->type == _RINT || redir->type == _HEREDOC)
			{
				redir->fd_int = 1;
				redir->fd_out = 0;
				if ((redir->file_int = ft_memalloc(sizeof(char) *
								((*x - start_file) + 1))) == NULL)
					return (1);
				ft_memcpy(redir->file_int, buf->c + start_file,
						*x - start_file);
			}
			break ;
		}
	}
	return (0);
}

static int	creat_file_name(t_lchar *buf, int start_redir, int end_redir,
		t_redirections *redir)
{
	int		x;
	int		type;
	int		find_a_file;

	type = 0;
	x = start_redir;
	init_struct_redir(redir);
	while (x < end_redir)
	{
		if (buf->type[x] == _ROUT || buf->type[x] == _RINT ||
				buf->type[x] == _APPROUT || buf->type[x] == _HEREDOC)
		{
			redir->type = buf->type[x];
			find_a_file = 1;
		}
		if (find_a_file == 1 && buf->type[x] == _FILE_NAME)
		{
			is_a_file_name(buf, &x, end_redir, redir);
			find_a_file = 0;
		}
		x++;
	}
	return (0);
}

static int	nbr_of_redir(t_lchar *buf, int x, int end_pipe)
{
	int		nbr_redir;

	nbr_redir = 0;
	while (x < end_pipe)
	{
		if (buf->type[x] == _ROUT || buf->type[x] == _RINT ||
				buf->type[x] == _APPROUT || buf->type[x] == _HEREDOC)
			nbr_redir++;
		x++;
	}
	return (nbr_redir);
}

int			creat_redirection(t_lchar *buf, int start_pipe, int end_pipe,
		t_pipelines *pipe)
{
	int		x;
	int		nbr_redir;
	int		start_redir;

	pipe->len = nbr_of_redir(buf, start_pipe, end_pipe);
	if ((pipe->redir = ft_memalloc(sizeof(t_pipelines) * (pipe->len + 1))) == NULL)
		return (1);
	nbr_redir = -1;
	x = start_pipe;
	start_redir = start_pipe;
	printf("end_pipe = [%d]\n", end_pipe);
	while (1)
	{
		printf("type = [%s]\n", which_define(buf->type[x]));
		if (x >= end_pipe || (buf->type[x] == _ROUT || buf->type[x] == _RINT || buf->type[x] == _HEREDOC
					|| buf->type[x] == _APPROUT || buf->type[x] == _DUP_ROUT
					|| buf->type[x] == _DUP_RINT || buf->type[x] == _ROUTERR))
		{
			printf("start_redir = [%d]\nend_redir = [%d]\n", start_redir, x);
			if (nbr_redir != -1)
				creat_file_name(buf, start_redir, x, &pipe->redir[nbr_redir]);
			start_redir = x;
			nbr_redir++;
			if (x > end_pipe)
				break ;
		}
		x++;
	}
	return (0);
}
