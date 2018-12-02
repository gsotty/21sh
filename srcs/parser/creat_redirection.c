#include "../../include/parser.h"

static int	creat_file_name(t_lchar *buf, int x, int end_redir,
		t_redirections *redir)
{
	int	start_file;

	redir->fd_int = 0;
	redir->fd_out = 1;
	redir->len_heredoc = 0;
	while (x <= end_redir)
	{
		if (buf->type[x] == _FILE_NAME)
		{
			start_file = x;
			while (buf->type[x] == _FILE_NAME)
			{
				x++;
				if (end_redir < x || buf->type[x] != _FILE_NAME)
				{
					if (redir->type == _ROUT || redir->type == _APPROUT)
					{
						if ((redir->file_out = ft_memalloc(sizeof(char) *
										((x - start_file) + 1))) == NULL)
							return (1);
						ft_memcpy(redir->file_out, buf->c + start_file,
								x - start_file);
					}
					else if (redir->type == _RINT || redir->type == _HEREDOC)
					{
						if ((redir->file_int = ft_memalloc(sizeof(char) *
										((x - start_file) + 1))) == NULL)
							return (1);
						ft_memcpy(redir->file_int, buf->c + start_file,
								x - start_file);
					}
					break ;
				}
			}
			break ;
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
	if ((pipe->redir = ft_memalloc(sizeof(t_redirections) * (pipe->len + 1))) == NULL)
		return (1);
	nbr_redir = -1;
	x = start_pipe;
	while (x <= end_pipe)
	{
		if (x < end_pipe && (buf->type[x] == _ROUT || buf->type[x] == _RINT || buf->type[x] == _HEREDOC
					|| buf->type[x] == _APPROUT || buf->type[x] == _DUP_ROUT
					|| buf->type[x] == _DUP_RINT || buf->type[x] == _ROUTERR))
		{
			if (nbr_redir != -1)
				creat_file_name(buf, start_redir, x - 1, &pipe->redir[nbr_redir]);
			nbr_redir++;
			start_redir = x + 1;
			pipe->redir[nbr_redir].type = buf->type[x];
		}
		else if (x >= end_pipe && nbr_redir != -1)
		{
			creat_file_name(buf, start_redir, x, &pipe->redir[nbr_redir]);
			break ;
		}
		x++;
	}
	return (0);
}
