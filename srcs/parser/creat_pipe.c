#include "../../include/parser.h"

static int	nbr_of_pipe(t_lchar *buf, int x, int end_sep)
{
	int		nbr_pipe;

	nbr_pipe = 0;
	while (1)
	{
		if (buf->type[x] == _PIPE && (x < 1 ? 1 :
				(buf->type[x - 1] != _GUILLEMET_RIGHT)))
		{
			nbr_pipe++;
		}
		if (x >= end_sep)
		{
			nbr_pipe++;
			break ;
		}
		x++;
	}
	return (nbr_pipe);
}

static int	copy_pipe(t_lchar *buf, int x, int end_sep, t_separateurs *sep, t_history *history)
{
	int		nbr_pipe;
	int		start_pipe;

	nbr_pipe = 0;
	start_pipe = x;
	while (1)
	{
		if (buf->type[x] == _PIPE && (x < 1 ? 1 :
				(buf->type[x - 1] != _GUILLEMET_RIGHT)))
		{
			if (creat_cmd(buf, start_pipe, x - 1, &sep->pipel[nbr_pipe], history) == 1)
				return (1);
			start_pipe = x + 1;
			nbr_pipe++;
		}
		if (x >= end_sep)
		{
			if (creat_cmd(buf, start_pipe, x, &sep->pipel[nbr_pipe], history) == 1)
				return (1);
			break ;
		}
		x++;
	}
	return (0);
}

int			creat_pipe(t_lchar *buf, int start_sep, int end_sep,
		t_separateurs *sep, t_history *history)
{
	if (start_sep > end_sep)
	{
		sep->len = 1;
		if ((sep->pipel = ft_memalloc(sizeof(t_pipelines) * sep->len)) == NULL)
			return (1);
		sep->pipel->argc = 1;
		if ((sep->pipel->argv = ft_memalloc(sizeof(t_typecmd *) *
						sep->pipel->argc)) == NULL)
			return (1);
		if ((sep->pipel->argv[0] = ft_memalloc(sizeof(t_typecmd))) == NULL)
			return (1);
		sep->pipel->argv[0]->len = 1;
		if ((sep->pipel->argv[0]->c = ft_memalloc(sizeof(char) *
						sep->pipel->argv[0]->len)) == NULL)
			return (1);
		if ((sep->pipel->argv[0]->type = ft_memalloc(sizeof(int) *
						sep->pipel->argv[0]->len)) == NULL)
			return (1);
	}
	else
	{
		sep->len = nbr_of_pipe(buf, start_sep, end_sep);
		if ((sep->pipel = ft_memalloc(sizeof(t_pipelines) * (sep->len + 1))) == NULL)
			return (1);
		if (copy_pipe(buf, start_sep, end_sep, sep, history) == 1)
			return (1);
	}
	return (0);
}
