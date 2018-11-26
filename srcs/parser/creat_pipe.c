#include "../../include/parser.h"

int		creat_pipe(t_lchar *buf, int start_sep, int end_sep, t_separateurs *sep)
{
	int		x;
	int		nbr_pipe;
	int		start_pipe;

	x = start_sep;
	nbr_pipe = 1;
	while (x < end_sep)
	{
		if (buf->type[x] == _PIPE)
			nbr_pipe++;
		x++;
	}
	sep->len = nbr_pipe;
	if ((sep->pipe = ft_memalloc(sizeof(t_pipelines) * (sep->len + 1))) == NULL)
		return (1);
	nbr_pipe = 0;
	x = start_sep;
	start_pipe = start_sep;
	while (1)
	{
		if (end_sep < x || buf->type[x] == _PIPE)
		{
			creat_cmd(buf, start_pipe, x, &sep->pipe[nbr_pipe]);
			creat_redirection(buf, start_pipe, x, &sep->pipe[nbr_pipe]);
			start_pipe = x;
			nbr_pipe++;
			if (end_sep < x)
				break ;
		}
		x++;
	}
	return (0);
}

