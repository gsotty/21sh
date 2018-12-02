#include "../../include/parser.h"

static int	nbr_of_pipe(t_lchar *buf, int x, int end_sep)
{
	int		nbr_pipe;

	nbr_pipe = 1;
	while (x < end_sep)
	{
		if (buf->type[x] == _PIPE)
			nbr_pipe++;
		x++;
	}
	return (nbr_pipe);
}

int			creat_pipe(t_lchar *buf, int start_sep, int end_sep,
		t_separateurs *sep)
{
	int		x;
	int		nbr_pipe;
	int		start_pipe;

	sep->len = nbr_of_pipe(buf, start_sep, end_sep);
	if ((sep->pipe = ft_memalloc(sizeof(t_pipelines) * (sep->len + 1))) == NULL)
		return (1);
	nbr_pipe = 0;
	x = start_sep;
	start_pipe = start_sep;
	while (x <= end_sep)
	{
		if (x < end_sep && buf->type[x] == _PIPE)
		{
			creat_cmd(buf, start_pipe, x - 1, &sep->pipe[nbr_pipe]);
			creat_redirection(buf, start_pipe, x - 1, &sep->pipe[nbr_pipe]);
			start_pipe = x + 1;
			nbr_pipe++;
		}
		else if (x >= end_sep)
		{
			creat_cmd(buf, start_pipe, x, &sep->pipe[nbr_pipe]);
			creat_redirection(buf, start_pipe, x, &sep->pipe[nbr_pipe]);
			break ;
		}
		x++;
	}
	return (0);
}
