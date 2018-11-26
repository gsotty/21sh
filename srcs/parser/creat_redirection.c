#include "../../include/parser.h"

int		creat_file_name(t_lchar *buf, int start_redir, int end_redir, t_redirections *redir)
{
	int		x;
	int		type;
	int		start_file;
	int		find_a_file;

	type = 0;
	x = start_redir;
	redir->fd_int = -1;
	redir->fd_out = -1;
	while (x < end_redir)
	{
		//	if (end_pipe < x || (buf->type[x] == _ROUT || buf->type[x] == _RINT || buf->type[x] == _HEREDOC || buf->type[x] == _APPROUT || buf->type[x] == _DUP_OUTPUT || buf->type[x] == _DUP_INTPUT || buf->type[x] == _ROUTERR))
		if (buf->type[x] == _ROUT || buf->type[x] == _RINT || buf->type[x] == _APPROUT || buf->type[x] == _HEREDOC)
		{
			redir->type = buf->type[x];
			find_a_file = 1;
		}
		start_file = x;
		while (find_a_file == 1 && buf->type[x] == _FILE_NAME)
		{
			x++;
			if (end_redir < x || buf->type[x] != _FILE_NAME)
			{
				if (redir->type == _ROUT || redir->type == _APPROUT)
				{
					redir->fd_int = 0;
					redir->fd_out = 1;
					if ((redir->file_out = ft_memalloc(sizeof(char) * ((x - start_file) + 1))) == NULL)
						return (1);
					ft_memcpy(redir->file_out, buf->c + start_file, x - start_file);
				}
				else if (redir->type == _RINT || redir->type == _HEREDOC)
				{
					redir->fd_int = 1;
					redir->fd_out = 0;
					if ((redir->file_int = ft_memalloc(sizeof(char) * ((x - start_file) + 1))) == NULL)
						return (1);
					ft_memcpy(redir->file_int, buf->c + start_file, x - start_file);
				}
				find_a_file = 0;
				break ;
			}
		}
		x++;
	}
	return (0);
}

int		creat_redirection(t_lchar *buf, int start_pipe, int end_pipe, t_pipelines *pipe)
{
	int		x;
	int		nbr_redir;
	int		start_redir;
	int		find_a_file;

	x = start_pipe;
	nbr_redir = 0;
	while (x < end_pipe)
	{
		if (buf->type[x] == _ROUT || buf->type[x] == _RINT || buf->type[x] == _APPROUT || buf->type[x] == _HEREDOC)
			nbr_redir++;
		x++;
	}
	pipe->len = nbr_redir;
	if ((pipe->redir = ft_memalloc(sizeof(t_pipelines) * (pipe->len + 1))) == NULL)
		return (1);
	nbr_redir = -1;
	find_a_file = 0;
	x = start_pipe;
	start_redir = start_pipe;
	while (1)
	{
		if (end_pipe < x || (buf->type[x] == _ROUT || buf->type[x] == _RINT || buf->type[x] == _HEREDOC || buf->type[x] == _APPROUT || buf->type[x] == _DUP_ROUT || buf->type[x] == _DUP_RINT || buf->type[x] == _ROUTERR))
		{
			if (nbr_redir != -1)
				creat_file_name(buf, start_redir, x, &pipe->redir[nbr_redir]);
			start_redir = x;
			nbr_redir++;
			if (end_pipe < x)
				break ;
		}
		x++;
	}
	return (0);
}

