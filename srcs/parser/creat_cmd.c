#include "../../include/parser.h"

// redir: <, >, >|, <<, >>, <&, >&, <>, (<<-, <&-, >&-) non c'est si le word et
// egale a "-"

static int		ft_atoi_redir(char *str, int len)
{
	int		i;
	int		ret_atoi;

	i = 0;
	ret_atoi = 0;
	while (i < len && str[i] >= '0' && str[i] <= '9')
	{
		ret_atoi *= 10;
		ret_atoi += (str[i] - 48);
		i++;
	}
	return (ret_atoi);
}

int		which_redir(t_lchar *buf, int x, int start_cmd, int end_cmd)
{
	if (x + 1 <= end_cmd)
	{
		if (buf->type[x] == _GUILLEMET_RIGHT && (buf->type[x + 1] == _PIPE
					|| buf->type[x + 1] == _GUILLEMET_RIGHT
					|| buf->type[x + 1] == _AMPERSAND))
			return (1);
		if (buf->type[x] == _GUILLEMET_LEFT &&
				(buf->type[x + 1] == _GUILLEMET_LEFT
				 || buf->type[x + 1] == _GUILLEMET_RIGHT
				 || buf->type[x + 1] == _AMPERSAND))
			return (1);
	}
	if (x <= end_cmd)
	{
		if (buf->type[x] == _GUILLEMET_RIGHT ||
				buf->type[x] == _GUILLEMET_LEFT)
			return (0);
	}
	return (-1);
}

int				ft_isacmd(int c)
{
	if (c == _DIGIT || c == _ALPHA || c == 33 || (c > 35 && c < 38) ||
			(c > 42 && c < 47))
		return (1);
	return (0);
}

static int	ft_onlydigit(int *type, int len)
{
	int		x;

	x = 0;
	while (x < len && type[x] == _DIGIT)
		x++;
	if (x == len)
		return (_INTFD);
	return (_WORD);
}

static int	nbr_of_redir(int *after_redir, t_lchar *buf, int start_cmd, int end_cmd)
{
	int		nbr_redir;
	int		start;
	int		x;
	int		ret;

	x = start_cmd;
	nbr_redir = 0;
	start = x;
	while (1)
	{
		if ((ret = which_redir(buf, x, start_cmd, end_cmd)) != -1)
		{
			if (x == start)
			{
				if (*after_redir == 1)
				{
					write(2, "ERROR: parser error near `", 26);
					write(2, buf->c + x, ret + 1);
					write(2, "'\n", 2);
					return (-1);
				}
				else
					*after_redir = 1;
				start = x + (ret + 1);
			}
			else
			{
				if (_INTFD == ft_onlydigit(buf->type + start, (x - start)))
				{
					if (*after_redir == 1)
					{
						write(2, "ERROR: parser error near `", 26);
						write(2, buf->c + x, x + ret + 1);
						write(2, "'\n", 2);
						return (-1);
					}
				}
				else
				{
					if (*after_redir == 1)
						*after_redir = 0;
					nbr_redir++;
				}
				start = x + (ret + 1);
				*after_redir = 1;
			}
			x = x + (ret + 1);
			if (x > end_cmd)
				break ;
		}
		else if (x >= end_cmd)
		{
			if (*after_redir == 1)
				*after_redir = 0;
			nbr_redir++;
			break;
		}
		else
			x++;
	}
	return (nbr_redir);
}

static	int		nbr_of_cmd(t_lchar *buf, int x, int end_pipe)
{
	int		nbr_argc;
	int		start_cmd;
	int		add_redir;
	int		after_redir;

	nbr_argc = 0;
	while (buf->type[x] == _SPACE && x <= end_pipe)
		x++;
	start_cmd = x;
	if (x <= end_pipe)
	{
		after_redir = 0;
		while (1)
		{
			if (buf->type[x] == _SPACE)
			{
				add_redir = nbr_of_redir(&after_redir, buf, start_cmd, (x - 1));
				if (add_redir == -1)
					return (add_redir);
				while (buf->type[x] == _SPACE && x <= end_pipe)
					x++;
				if (x > end_pipe)
				{
					nbr_argc = add_redir + nbr_argc;
					break ;
				}
				start_cmd = x;
				nbr_argc = add_redir + nbr_argc;
			}
			if (x >= end_pipe)
			{
				add_redir = nbr_of_redir(&after_redir, buf, start_cmd, x);
				if (add_redir == -1)
					return (add_redir);
				if (after_redir == 1)
				{
					write(2, "ERROR: parser error near `\\n'\n", 30);
					//	write(2, buf->c + x, x + ret + 1);
					//	write(2, "'\n", 1);
					return (-1);
				}
				if (buf->type[x] != _SPACE)
					nbr_argc = add_redir + nbr_argc;
				break ;
			}
			x++;
		}
	}
	return (nbr_argc);
}

static t_typecmd	*ft_typecmddup(t_typecmd *dest, t_lchar *srs, int start, int n)
{
	int		x;

	dest->len = (n - start) + 1;
	if ((dest->c = ft_memalloc(sizeof(char) * (dest->len + 1))) == NULL)
		return (NULL);
	if ((dest->type = ft_memalloc(sizeof(int) * (dest->len + 1))) == NULL)
		return (NULL);
	x = 0;
	while (x < dest->len)
	{
		dest->c[x] = srs->c[x + start];
		dest->type[x] = srs->type[x + start];
		x++;
	}
	return (dest);
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

int		add_fd_value(t_typecmd *argv, t_history *history)
{
	char	*nbr;

	if (argv->type_cmd == _DUPOUT)
	{
		if (argv->digit == -1)
			argv->l_fd = 1;
		else
			argv->l_fd = argv->digit;
		if (_INTFD == ft_onlydigit(argv->file->type, argv->file->len))
		{
			argv->r_fd = ft_atoi_redir(argv->file->c, argv->file->len);
			if (isatty(argv->r_fd) == 1)
			{
				if (argv->file->len == 1 && argv->file->c[0] == '-')
					argv->r_fd = -1;
	//			else
	//				argv->r_fd = open(argv->file->c, O_WRONLY | O_CREAT
	//						| O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			}
			else
			{
				write(2, "21sh: ", 6);
				nbr = ft_itoa(argv->r_fd);
				write(2, nbr, ft_strlen(nbr));
				free(nbr);
				write(2, ": bad file descriptor\n", 22);
				return (1);
			}
		}
		else
		{
			if (argv->file->len == 1 && argv->file->c[0] == '-')
				argv->r_fd = -1;
//			else
//				argv->r_fd = open(argv->file->c, O_WRONLY | O_CREAT
//						| O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		}
	}
	if (argv->type_cmd == _APPROUT)
	{
		if (argv->digit == -1)
			argv->l_fd = 1;
		else
			argv->l_fd = argv->digit;
		if ((argv->r_fd = open(argv->file->c, O_WRONLY | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		{
			printf("error: open\n");
			return (1);
		}
	}
	if (argv->type_cmd == _DUPINT)
	{
		if (argv->digit == -1)
			argv->l_fd = 0;
		else
			argv->l_fd = argv->digit;
		if (_INTFD == ft_onlydigit(argv->file->type, argv->file->len))
		{
			argv->r_fd = ft_atoi_redir(argv->file->c, argv->file->len);
			if (isatty(argv->r_fd) == 1)
			{
				if (argv->file->len == 1 && argv->file->c[0] == '-')
					argv->r_fd = -1;
		//		else
		//			argv->r_fd = open(argv->file->c, O_WRONLY | O_CREAT
		//					| O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			}
			else
			{
				write(2, "21sh: ", 6);
				nbr = ft_itoa(argv->r_fd);
				write(2, nbr, ft_strlen(nbr));
				free(nbr);
				write(2, ": bad file descriptor\n", 22);
				return (1);
			}
		}
		else
		{
			if (argv->file->len == 1 && argv->file->c[0] == '-')
				argv->r_fd = -1;
//			else
//				argv->r_fd = open(argv->file->c, O_WRONLY | O_CREAT | O_TRUNC,
//						S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		}
	}
	if (argv->type_cmd == _RRDWR)
	{
		if (argv->digit == -1)
			argv->l_fd = 0;
		else
			argv->l_fd = argv->digit;
		if ((argv->r_fd = open(argv->file->c, O_RDWR | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		{
			printf("error: open\n");
			return (1);
		}
	}
	if (argv->type_cmd == _HEREDOC)
	{
		if (argv->digit == -1)
			argv->l_fd = 0;
		else
			argv->l_fd = argv->digit;
		argv->r_fd = -1;
		if (creat_here_document(argv, argv->file->c, history) == 1)
			return (1);
	}
	if (argv->type_cmd == _ROUT)
	{
		if (argv->digit == -1)
			argv->l_fd = 1;
		else
			argv->l_fd = argv->digit;
		if ((argv->r_fd = open(argv->file->c, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		{
			printf("error: open\n");
			return (1);
		}
	}
	if (argv->type_cmd == _RINT)
	{
		if (argv->digit == -1)
			argv->l_fd = 0;
		else
			argv->l_fd = argv->digit;
		if ((argv->r_fd = open(argv->file->c, O_RDONLY)) == -1)
		{
			printf("error: open\n");
			return (1);
		}
	}
	return (0);
}

int		which_type(t_typecmd *argv, t_lchar *buf, int start, int len)
{
	if (len == 2)
	{
		if (buf->type[start] == _GUILLEMET_RIGHT &&
				buf->type[start + 1] == _AMPERSAND)
			return (_DUPOUT);
		if (buf->type[start] == _GUILLEMET_RIGHT &&
				buf->type[start + 1] == _GUILLEMET_RIGHT)
			return (_APPROUT);
		if (buf->type[start] == _GUILLEMET_RIGHT &&
				buf->type[start + 1] == _PIPE)
			return (_ROUT);
		if (buf->type[start] == _GUILLEMET_LEFT &&
				buf->type[start + 1] == _AMPERSAND)
			return (_DUPINT);
		if (buf->type[start] == _GUILLEMET_LEFT &&
				buf->type[start + 1] == _GUILLEMET_RIGHT)
			return (_RRDWR);
		if (buf->type[start] == _GUILLEMET_LEFT &&
				buf->type[start + 1] == _GUILLEMET_LEFT)
			return (_HEREDOC);
	}
	if (len == 1)
	{
		if (buf->type[start] == _GUILLEMET_RIGHT)
			return (_ROUT);
		if (buf->type[start] == _GUILLEMET_LEFT)
			return (_RINT);
	}
	return (-1);
}

int			add_fd_redir(t_typecmd *buf)
{
	return (0);
}

static int	copy_redir(int *after_redir, t_lchar *buf, int block, int nbr_argc,
		int start_cmd, int end_cmd, t_pipelines *pipel, t_history *history)
{
	int		start;
	int		x;
	int		ret;
	int		count_lchar;

	x = start_cmd;
	start = x;
	while (1)
	{
		if ((ret = which_redir(buf, x, start_cmd, end_cmd)) != -1)
		{
			if (x == start)
			{
				if ((pipel->argv[nbr_argc] = ft_memalloc(sizeof(t_typecmd))) == NULL)
					return (-1);
				pipel->argv[nbr_argc]->digit = -1;
				pipel->argv[nbr_argc]->block = block;
				pipel->argv[nbr_argc]->type_cmd = which_type(pipel->argv[nbr_argc],
						buf, start, 1 + ret);
				ft_typecmddup(pipel->argv[nbr_argc], buf, start, (x + ret));
				*after_redir = 1;
				start = x + (ret + 1);
			}
			else
			{
				if (_INTFD == ft_onlydigit(buf->type + start, (x - start)))
				{
					if ((pipel->argv[nbr_argc] = ft_memalloc(sizeof(t_typecmd))) == NULL)
						return (-1);
					pipel->argv[nbr_argc]->digit = -1;
					pipel->argv[nbr_argc]->digit =
						ft_atoi_redir(buf->c + start, (x - start));
					start = x;
					pipel->argv[nbr_argc]->block = block;
					pipel->argv[nbr_argc]->type_cmd = which_type(pipel->argv[nbr_argc],
							buf, start, 1 + ret);
					ft_typecmddup(pipel->argv[nbr_argc], buf, start, (x + ret));
				}
				else
				{
					if (*after_redir == 1)
					{
						if ((pipel->argv[nbr_argc]->file = ft_memalloc(sizeof(t_lchar) + 1)) == NULL)
							return (-1);
						if ((pipel->argv[nbr_argc]->file->c = ft_memalloc(sizeof(char)
										* (x - start) + 1)) == NULL)
							return (-1);
						if ((pipel->argv[nbr_argc]->file->type = ft_memalloc(sizeof(int)
										* (x - start) + 1)) == NULL)
							return (-1);
						pipel->argv[nbr_argc]->file->len = x - start;
						count_lchar = 0;
						while (count_lchar < (x - start))
						{
							pipel->argv[nbr_argc]->file->c[count_lchar] = buf->c[count_lchar + start];
							pipel->argv[nbr_argc]->file->type[count_lchar] = buf->type[count_lchar + start];
							count_lchar++;
						}
						*after_redir = 0;
						if (add_fd_value(pipel->argv[nbr_argc], history) == 1)
							return (-1);
						nbr_argc++;
						start = x;
						if ((pipel->argv[nbr_argc] = ft_memalloc(sizeof(t_typecmd))) == NULL)
							return (-1);
						pipel->argv[nbr_argc]->digit = -1;
						pipel->argv[nbr_argc]->type_cmd = which_type(pipel->argv[nbr_argc],
								buf, start, 1 + ret);
						ft_typecmddup(pipel->argv[nbr_argc], buf, start, (x + ret));
					}
					else
					{
						if ((pipel->argv[nbr_argc] = ft_memalloc(sizeof(t_typecmd))) == NULL)
							return (-1);
						pipel->argv[nbr_argc]->digit = -1;
						pipel->argv[nbr_argc]->block = block;
						pipel->argv[nbr_argc]->type_cmd = _WORD;
						ft_typecmddup(pipel->argv[nbr_argc], buf, start, (x - 1));
						if (add_fd_value(pipel->argv[nbr_argc], history) == 1)
							return (-1);
						nbr_argc++;
						start = x;
						if ((pipel->argv[nbr_argc] = ft_memalloc(sizeof(t_typecmd))) == NULL)
							return (-1);
						pipel->argv[nbr_argc]->digit = -1;
						pipel->argv[nbr_argc]->block = block;
						pipel->argv[nbr_argc]->type_cmd = which_type(pipel->argv[nbr_argc],
								buf, start, 1 + ret);
						ft_typecmddup(pipel->argv[nbr_argc], buf, start, (x + ret));
					}
				}
				*after_redir = 1;
				start = x + (ret + 1);
			}
			x = x + (ret + 1);
			if (x > end_cmd)
				break ;
		}
		else if (x >= end_cmd)
		{
			if (*after_redir == 1)
			{
				if ((pipel->argv[nbr_argc]->file = ft_memalloc(sizeof(t_lchar) + 1)) == NULL)
					return (-1);
				if ((pipel->argv[nbr_argc]->file->c = ft_memalloc(sizeof(char) * ((x + 1) - start) + 1)) == NULL)
					return (-1);
				if ((pipel->argv[nbr_argc]->file->type = ft_memalloc(sizeof(int) * ((x + 1) - start) + 1)) == NULL)
					return (-1);
				pipel->argv[nbr_argc]->file->len = (x + 1) - start;
				count_lchar = 0;
				while (count_lchar < ((x + 1) - start))
				{
					pipel->argv[nbr_argc]->file->c[count_lchar] = buf->c[count_lchar + start];
					pipel->argv[nbr_argc]->file->type[count_lchar] = buf->type[count_lchar + start];
					count_lchar++;
				}
				*after_redir = 0;
			}
			else
			{
				if ((pipel->argv[nbr_argc] = ft_memalloc(sizeof(t_typecmd))) == NULL)
					return (-1);
				pipel->argv[nbr_argc]->digit = -1;
				pipel->argv[nbr_argc]->block = block;
				pipel->argv[nbr_argc]->type_cmd = _WORD;
				ft_typecmddup(pipel->argv[nbr_argc], buf, start, x);
			}
			if (add_fd_value(pipel->argv[nbr_argc], history) == 1)
				return (-1);
			nbr_argc++;
			break;
		}
		else
			x++;
	}
	return (nbr_argc);
}

static int		copy_cmd(t_lchar *buf, int x, int end_pipe, t_pipelines *pipel, t_history *history)
{
	int		nbr_argc;
	int		start_cmd;
	int		block;
	int		after_redir;

	nbr_argc = 0;
	while (buf->type[x] == _SPACE && x <= end_pipe)
		x++;
	if (x >= end_pipe)
	{
		pipel->argc = 1;
		if ((pipel->argv[0] = ft_memalloc(sizeof(t_typecmd))) == NULL)
			return (1);
		pipel->argv[0]->len = 1;
		if ((pipel->argv[0]->c = ft_memalloc(sizeof(char) *
						pipel->argv[0]->len)) == NULL)
			return (1);
		return (0);
	}
	start_cmd = x;
	block = 0;
	after_redir = 0;
	while (1)
	{
		if (buf->type[x] == _SPACE)
		{
			if ((nbr_argc = copy_redir(&after_redir, buf, block, nbr_argc, start_cmd, x - 1, pipel, history)) == -1)
				return (1);
			block++;
			while (buf->type[x] == _SPACE && x <= end_pipe)
				x++;
			if (x > end_pipe)
				break ;
			start_cmd = x;
		}
		if (x >= end_pipe)
		{
			if (buf->type[x] != _SPACE)
			{
				if ((nbr_argc = copy_redir(&after_redir, buf, block, nbr_argc, start_cmd, x, pipel, history)) == -1)
					return (1);
				block++;
			}
			break ;
		}
		x++;
	}
	return (0);
}

int				creat_cmd(t_lchar *buf, int start_pipe, int end_pipe,
		t_pipelines *pipel, t_history *history)
{
	if (start_pipe >= end_pipe)
	{
		pipel->argc = 1;
		if ((pipel->argv = ft_memalloc(sizeof(t_typecmd *) *
						pipel->argc)) == NULL)
			return (1);
		if ((pipel->argv[0] = ft_memalloc(sizeof(t_typecmd))) == NULL)
			return (1);
		pipel->argv[0]->len = 1;
		if ((pipel->argv[0]->c = ft_memalloc(sizeof(char) *
						pipel->argv[0]->len)) == NULL)
			return (1);
		if ((pipel->argv[0]->type = ft_memalloc(sizeof(int) *
						pipel->argv[0]->len)) == NULL)
			return (1);
	}
	else
	{
		pipel->argc = nbr_of_cmd(buf, start_pipe, end_pipe);
		if (pipel->argc == -1)
			return (1);
		if ((pipel->argv = ft_memalloc(sizeof(t_typecmd *) *
						(pipel->argc + 1))) == NULL)
			return (1);
		if (copy_cmd(buf, start_pipe, end_pipe, pipel, history) == 1)
			return (1);
	}
	return (0);
}
