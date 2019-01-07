#include "../../include/parser.h"

static	int		nbr_of_cmd(t_lchar *buf, int x, int end_pipe)
{
	int		nbr_argc;

	nbr_argc = 0;
	while (x <= end_pipe)
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
	return (nbr_argc);
}

static int		copy_cmd(t_lchar *buf, int x, int end_pipe, t_pipelines *pipel)
{
	int		nbr_argc;
	int		start_argc;

	nbr_argc = 0;
	while (x < end_pipe)
	{
		start_argc = x;
		while (buf->type[x] == _WORD)
		{
			x++;
			if (end_pipe < x || buf->type[x] != _WORD)
			{
				if ((pipel->argv[nbr_argc] = ft_memalloc(sizeof(char) *
								((x - start_argc) + 1))) == NULL)
					return (1);
				ft_memcpy(pipel->argv[nbr_argc], buf->c + start_argc,
						x - start_argc);
				pipel->argv[nbr_argc][x - start_argc] = '\0';
				nbr_argc++;
				break ;
			}
		}
		x++;
	}
	return (0);
}

int				creat_cmd(t_lchar *buf, int start_pipe, int end_pipe,
		t_pipelines *pipel)
{
	pipel->argc = nbr_of_cmd(buf, start_pipe, end_pipe);
	if ((pipel->argv = ft_memalloc(sizeof(char *) *
					(pipel->argc + 1))) == NULL)
		return (1);
	if (copy_cmd(buf, start_pipe, end_pipe, pipel) == 1)
		return (1);
	return (0);
}
