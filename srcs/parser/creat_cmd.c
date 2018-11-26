#include "../../include/parser.h"

int		creat_cmd(t_lchar *buf, int start_pipe, int end_pipe, t_pipelines *pipe)
{
	int		x;
	int		nbr_argc;
	int		start_argc;

	x = start_pipe;
	nbr_argc = 0;
	while (x < end_pipe)
	{
		while (buf->type[x] == _WORD)
		{
			x++;
			if (end_pipe < x || buf->type[x] != _WORD)
			{
				nbr_argc++;
				break ;
			}
		}
		x++;
	}
	pipe->argc = nbr_argc;
	if ((pipe->argv = ft_memalloc(sizeof(char *) * (pipe->argc + 1))) == NULL)
		return (1);
	nbr_argc = 0;
	x = start_pipe;
	start_argc = start_pipe;
	while (1)
	{
		start_argc = x;
		while (buf->type[x] == _WORD)
		{
			x++;
			if (end_pipe < x || buf->type[x] != _WORD)
			{
				if ((pipe->argv[nbr_argc] = ft_memalloc(sizeof(char) * ((x - start_argc) + 1))) == NULL)
					return (1);
				ft_memcpy(pipe->argv[nbr_argc], buf->c + start_argc, x - start_argc);
				nbr_argc++;
				break ;
			}
		}
		if (end_pipe < x)
			break ;
		x++;
	}
	return (0);
}

