#include "../../include/parser.h"

#include <stdio.h>

void	ft_print_lchar(t_lchar *buf)
{
	int		x;
	char	*nbr;

	x = 0;
	while (x < buf->len)
	{
		write(0, "buf = [", 7);
		nbr = ft_itoa(x);
		write(0, nbr, ft_strlen(nbr));
		free(nbr);
		write(0, "], [", 4);
		write(0, buf->c + x, 1);
		write(0, "], [", 4);
		write(0, which_define(buf->type[x]), ft_strlen(which_define(buf->type[x])));
		write(0, "]\n", 2);
		x++;
	}
}

void	print_base(t_parser_shell base)
{
	int		x;
	int		y;
	int		z;
	int		a;
	char	*nbr;

	x = 0;
	write(0, "len sep [", 9);
	nbr = ft_itoa(base.len);
	write(0, nbr, ft_strlen(nbr));
	free(nbr);
	write(0, "]\n", 2);
	while (x < base.len)
	{
		write(0, "	sep [", 6);
		nbr = ft_itoa(x);
		write(0, nbr, ft_strlen(nbr));
		free(nbr);
		write(0, "]\n", 2);
		write(0, "	len pipe [", 11);
		nbr = ft_itoa(base.sep[x].len);
		write(0, nbr, ft_strlen(nbr));
		free(nbr);
		write(0, "]\n", 2);
		y = 0;
		while (y < base.sep[x].len) 
		{
			write(0, "		pipe [", 8);
			nbr = ft_itoa(y);
			write(0, nbr, ft_strlen(nbr));
			free(nbr);
			write(0, "]\n", 2);
			write(0, "		len cmd [", 11);
			nbr = ft_itoa(base.sep[x].pipe[y].argc);
			write(0, nbr, ft_strlen(nbr));
			free(nbr);
			write(0, "]\n", 2);
			z = 0;
			a = 0;
			while (z < base.sep[x].pipe[y].argc)
			{
				write(0, "			cmp [", 9);
				nbr = ft_itoa(z);
				write(0, nbr, ft_strlen(nbr));
				free(nbr);
				write(0, "]\n", 2);
				write(0, "				argv [", 10);
				write(0, base.sep[x].pipe[y].argv[z], ft_strlen(base.sep[x].pipe[y].argv[z]));
				write(0, "]\n", 2);
				z++;
			}
			write(0, "		len redir [", 13);
			nbr = ft_itoa(base.sep[x].pipe[y].len);
			write(0, nbr, ft_strlen(nbr));
			free(nbr);
			write(0, "]\n", 2);
			while (a < base.sep[x].pipe[y].len)
			{
				write(0, "			redir [", 10);
				nbr = ft_itoa(a);
				write(0, nbr, ft_strlen(nbr));
				free(nbr);
				write(0, "]\n", 2);
				write(0, "				type [", 10);
				write(0, which_define(base.sep[x].pipe[y].redir[a].type), ft_strlen(which_define(base.sep[x].pipe[y].redir[a].type)));
				write(0, "]\n", 2);
				write(0, "				fd_int [", 12);
				nbr = ft_itoa(base.sep[x].pipe[y].redir[a].fd_int);
				write(0, nbr, ft_strlen(nbr));
				free(nbr);
				write(0, "]\n", 2);
				write(0, "				file_int [", 14);
				if (base.sep[x].pipe[y].redir[a].file_int == NULL)
					write(0, "(NULL)", 6);
				else
					write(0, base.sep[x].pipe[y].redir[a].file_int, ft_strlen(base.sep[x].pipe[y].redir[a].file_int));
				write(0, "]\n", 2);
				write(0, "				fd_out [", 12);
				nbr = ft_itoa(base.sep[x].pipe[y].redir[a].fd_out);
				write(0, nbr, ft_strlen(nbr));
				free(nbr);
				write(0, "]\n", 2);
				write(0, "				file_out [", 14);
				if (base.sep[x].pipe[y].redir[a].file_out == NULL)
					write(0, "(NULL)", 6);
				else
					write(0, base.sep[x].pipe[y].redir[a].file_out, ft_strlen(base.sep[x].pipe[y].redir[a].file_out));
				write(0, "]\n", 2);
				write(0, "				len_here [", 14);
				nbr = ft_itoa(base.sep[x].pipe[y].redir[a].len_heredoc);
				write(0, nbr, ft_strlen(nbr));
				free(nbr);
				write(0, "]\n", 2);
				write(0, "				here [", 10);
				if (base.sep[x].pipe[y].redir[a].heredoc == NULL)
					write(0, "(NULL)", 6);
				else
					write(0, base.sep[x].pipe[y].redir[a].heredoc, ft_strlen(base.sep[x].pipe[y].redir[a].heredoc));
				write(0, "]\n", 2);
				a++;
			}
			y++;
		}
		x++;
	}
}

int				ft_history_copy_heredoc(t_history *history_first, t_history *history_copy)
{
	int			count;

	history_copy->len_buf = history_first->len_buf;
	history_copy->malloc_buf = history_first->len_buf;
	history_copy->pos_buf = history_first->pos_buf;
	if ((history_copy->len = ft_memalloc(sizeof(int) * (history_copy->malloc_buf + 1))) == NULL)
		return (1);
	if ((history_copy->len_malloc = ft_memalloc(sizeof(int) * (history_copy->malloc_buf + 1))) == NULL)
		return (1);
	if ((history_copy->pos = ft_memalloc(sizeof(int) * (history_copy->malloc_buf + 1))) == NULL)
		return (1);
	if ((history_copy->buf = ft_memalloc(sizeof(char *) * (history_copy->malloc_buf + 1))) == NULL)
		return (1);
	count = 0;
	while (count < history_first->len_buf)
	{
		history_copy->len[count] = history_first->len[count];
		history_copy->len_malloc[count] = history_first->len_malloc[count];
		history_copy->pos[count] = history_first->pos[count];
		if ((history_copy->buf[count] = ft_memalloc(sizeof(char) * (history_copy->len_malloc[count] + 1))) == NULL)
			return (1);
		ft_memcpy(history_copy->buf[count], history_first->buf[count], history_first->len[count]);
		count++;
	}
	return (0);
}

int		creat_heredoc(t_pipelines pipe, t_history *history_first, int z)
{
	int			len_heredoc;
	int			count_heredoc;
	int			start_heredoc;
	t_history	history_heredoc;
	t_history	history_copy;

	if (ft_history_copy_heredoc(history_first, &history_heredoc) == 1)
		return (1);
	start_heredoc = history_heredoc.pos_buf + 1;
	while (1)
	{
		if ((while_main(1, &history_heredoc, &history_copy)) == 1)
			return (1);
		if (ft_memcmp(pipe.redir[z].file_int , history_heredoc.buf[history_heredoc.pos_buf], history_heredoc.len[history_heredoc.pos_buf]) == 0)
		{
			break ;
		}
		write(0, "\n", 1);
	}
	count_heredoc = start_heredoc;
	len_heredoc = 0;
	while (count_heredoc < history_heredoc.len_buf)
	{
		len_heredoc += history_heredoc.len[count_heredoc];
		len_heredoc++;
		count_heredoc++;
	}
	if ((pipe.redir[z].heredoc = ft_memalloc((sizeof(char) * (len_heredoc + 1)))) == NULL)
		return (1);
	pipe.redir[z].len_heredoc = 0;
	count_heredoc = start_heredoc;
	while (count_heredoc < history_heredoc.len_buf)
	{
		ft_memcpy(pipe.redir[z].heredoc + pipe.redir[z].len_heredoc, history_heredoc.buf[count_heredoc], history_heredoc.len[count_heredoc]);
		pipe.redir[z].len_heredoc += history_heredoc.len[count_heredoc];
		ft_memcpy(pipe.redir[z].heredoc + pipe.redir[z].len_heredoc, "\n", 1);
		pipe.redir[z].len_heredoc++;
		count_heredoc++;
	}
	return (0);
}

int		how_close(t_separateurs sep, int *pipefd_one, int *pipefd_two, int count_pipe)
{
	int		z;

	z = 0;
	while (z < sep.pipe[count_pipe].len)
	{
		if (sep.pipe[count_pipe].redir[z].file_int != NULL)
		{
			if (sep.pipe[count_pipe].redir[z].type == _HEREDOC)
				close(pipefd_one[1]);
		}
		z++;
	}
	if (sep.len > 1)
	{
		if (count_pipe == 0)
			close(pipefd_one[0]);
		else if (count_pipe == (sep.len - 1))
			close(pipefd_two[1]);
		else
		{
			close(pipefd_one[0]);
			close(pipefd_two[1]);
		}
	}
	return (0);
}

int		while_write_here(t_pipelines pipe, int *pipefd, int fd_int, int fd_out)
{
	int		z;
	pid_t	father;

	z = 0;
	while (z < pipe.len)
	{
		if (pipe.redir[z].file_int != NULL)
		{
			if (pipe.redir[z].type == _RINT)
				close(fd_int);
			else if (pipe.redir[z].type == _HEREDOC)
			{
				father = fork();
				if (father == 0)
				{
					close(pipefd[0]);
					write(pipefd[1], pipe.redir[z].heredoc, pipe.redir[z].len_heredoc);
					exit(0);
				}
				else if (father > 0)
				{
					close(pipefd[0]);
					close(pipefd[1]);
				}
				else
				{
					write(2, "error fork\n", 11);
					return (1);
				}
			}
		}
		else if (pipe.redir[z].file_out != NULL)
		{
			if (pipe.redir[z].type == _APPROUT)
				close(fd_out);
			else if (pipe.redir[z].type == _ROUT)
				close(fd_out);
		}
		z++;
	}
	return (0);
}

int		fork_exec(t_separateurs sep, char **my_envp, int y, int *pipefd_one, int *pipefd_two, int fd_int, int fd_out)
{
	pid_t		father;

	father = fork();
	if (father == 0)
	{
		dup2(fd_int, 0);
		dup2(fd_out, 1);
		how_close(sep, pipefd_one, pipefd_two, y);
		exec_cmd(sep.pipe[y].argc, sep.pipe[y].argv, my_envp);
		exit(0);
	}
	else if (father > 0)
	{
		if (sep.len > 1)
		{
			if (y == 0)
			{
				while_write_here(sep.pipe[y], pipefd_two, fd_int, fd_out);
				close(pipefd_one[1]);
			}
			else if (y == (sep.len - 1))
			{
				close(pipefd_two[0]);
				while_write_here(sep.pipe[y], pipefd_two, fd_int, fd_out);
			}
			else
			{
				while_write_here(sep.pipe[y], pipefd_two, fd_int, fd_out);
				close(pipefd_one[1]);
				close(pipefd_two[0]);
			}
		}
		else
			while_write_here(sep.pipe[y], pipefd_two, fd_int, fd_out);
	}
	else
	{
		write(2, "error fork\n", 11);
		return (1);
	}
	return (0);
}

int		exec_base(t_parser_shell base, char **my_envp, t_history *history_first)
{
	int			status;
	int			rep;
	int			x;
	int			y;
	int			z;
	int			int_or_out;
	int			pipefd_one[2];
	int			pipefd_tow[2];
	int			fd_int;
	int			fd_out;

	x = 0;
	while (x < base.len)
	{
		fd_int = 0;
		fd_out = 1;
		y = 0;
		int_or_out = 0;
		while (y < base.sep[x].len) 
		{
			if (base.sep[x].len > 1)
			{
				if (y == 0)
				{
					if (pipe((int_or_out == 0 ? pipefd_one : pipefd_tow)) == -1)
					{
						write(2, "error pipe\n", 11);
						return (1);
					}
					fd_out = (int_or_out == 0 ? pipefd_one[1] : pipefd_tow[1]);
					z = 0;
					while (z < base.sep[x].pipe[y].len)
					{
						if (base.sep[x].pipe[y].redir[z].file_int != NULL)
						{
							if (base.sep[x].pipe[y].redir[z].type == _RINT)
								fd_int = open(base.sep[x].pipe[y].redir[z].file_int , O_RDONLY);
							else if (base.sep[x].pipe[y].redir[z].type == _HEREDOC)
							{
								creat_heredoc(base.sep[x].pipe[y], history_first, z);
								if (pipe((int_or_out == 1 ? pipefd_one : pipefd_tow)) == -1)
								{
									write(2, "error pipe\n", 11);
									return (1);
								}
								fd_int = (int_or_out == 1 ? pipefd_one[0] : pipefd_tow[0]);
							}
						}
						if (base.sep[x].pipe[y].redir[z].file_out != NULL)
						{
							if (base.sep[x].pipe[y].redir[z].type == _APPROUT)
								fd_out = open(base.sep[x].pipe[y].redir[z].file_out , O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
							else if (base.sep[x].pipe[y].redir[z].type == _ROUT)
								fd_out = open(base.sep[x].pipe[y].redir[z].file_out , O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
						}
						z++;
					}
				}
				else if (y == (base.sep[x].len - 1))
				{
					fd_int = (int_or_out == 1 ? pipefd_one[0] : pipefd_tow[0]);
					z = 0;
					while (z < base.sep[x].pipe[y].len)
					{
						if (base.sep[x].pipe[y].redir[z].file_int != NULL)
						{
							if (base.sep[x].pipe[y].redir[z].type == _RINT)
								fd_int = open(base.sep[x].pipe[y].redir[z].file_int , O_RDONLY);
							else if (base.sep[x].pipe[y].redir[z].type == _HEREDOC)
							{
								creat_heredoc(base.sep[x].pipe[y], history_first, z);
								if (pipe((int_or_out == 1 ? pipefd_one : pipefd_tow)) == -1)
								{
									write(2, "error pipe\n", 11);
									return (1);
								}
								fd_int = (int_or_out == 1 ? pipefd_one[0] : pipefd_tow[0]);
							}
						}
						if (base.sep[x].pipe[y].redir[z].file_out != NULL)
						{
							if (base.sep[x].pipe[y].redir[z].type == _APPROUT)
								fd_out = open(base.sep[x].pipe[y].redir[z].file_out , O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
							else if (base.sep[x].pipe[y].redir[z].type == _ROUT)
								fd_out = open(base.sep[x].pipe[y].redir[z].file_out , O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
						}
						z++;
					}
				}
				else
				{
					if (pipe((int_or_out == 0 ? pipefd_one : pipefd_tow)) == -1)
					{
						write(2, "error pipe\n", 11);
						return (1);
					}
					fd_int = (int_or_out == 1 ? pipefd_one[0] : pipefd_tow[0]);
					fd_out = (int_or_out == 0 ? pipefd_one[1] : pipefd_tow[1]);
					z = 0;
					while (z < base.sep[x].pipe[y].len)
					{
						if (base.sep[x].pipe[y].redir[z].file_int != NULL)
						{
							if (base.sep[x].pipe[y].redir[z].type == _RINT)
								fd_int = open(base.sep[x].pipe[y].redir[z].file_int , O_RDONLY);
							else if (base.sep[x].pipe[y].redir[z].type == _HEREDOC)
							{
								creat_heredoc(base.sep[x].pipe[y], history_first, z);
								if (pipe((int_or_out == 1 ? pipefd_one : pipefd_tow)) == -1)
								{
									write(2, "error pipe\n", 11);
									return (1);
								}
								fd_int = (int_or_out == 1 ? pipefd_one[0] : pipefd_tow[0]);
							}
						}
						if (base.sep[x].pipe[y].redir[z].file_out != NULL)
						{
							if (base.sep[x].pipe[y].redir[z].type == _APPROUT)
								fd_out = open(base.sep[x].pipe[y].redir[z].file_out , O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
							else if (base.sep[x].pipe[y].redir[z].type == _ROUT)
								fd_out = open(base.sep[x].pipe[y].redir[z].file_out , O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
						}
						z++;
					}
				}
			}
			else
			{
				z = 0;
				while (z < base.sep[x].pipe[y].len)
				{
					if (base.sep[x].pipe[y].redir[z].file_int != NULL)
					{
						if (base.sep[x].pipe[y].redir[z].type == _RINT)
							fd_int = open(base.sep[x].pipe[y].redir[z].file_int , O_RDONLY);
						else if (base.sep[x].pipe[y].redir[z].type == _HEREDOC)
						{
							creat_heredoc(base.sep[x].pipe[y], history_first, z);
							if (pipe((int_or_out == 1 ? pipefd_one : pipefd_tow)) == -1)
							{
								write(2, "error pipe\n", 11);
								return (1);
							}
							fd_int = (int_or_out == 1 ? pipefd_one[0] : pipefd_tow[0]);
						}
					}
					else if (base.sep[x].pipe[y].redir[z].file_out != NULL)
					{
						if (base.sep[x].pipe[y].redir[z].type == _APPROUT)
							fd_out = open(base.sep[x].pipe[y].redir[z].file_out , O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
						else if (base.sep[x].pipe[y].redir[z].type == _ROUT)
							fd_out = open(base.sep[x].pipe[y].redir[z].file_out , O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
					}
					z++;
				}
			}

			fork_exec(base.sep[x], my_envp, y, (int_or_out == 0 ? pipefd_one : pipefd_tow), (int_or_out == 1 ? pipefd_one : pipefd_tow), fd_int, fd_out);

			if (int_or_out == 0)
				int_or_out = 1;
			else
				int_or_out = 0;

			y++;
		}
		while ((rep = waitpid(-1, &status, 0)) > -1)
		{
			printf("wait = [%d], rep = [%d]\n", rep, WEXITSTATUS(status));
		}
		x++;
	}
	return (0);
}

int		parser(t_lchar *buf, char **my_envp, t_history *history_first)
{
	int				x;
	t_parser_shell	base;

	x = 0;
	(void)my_envp;
	while (x < buf->len)
	{
		if (buf->c[x] == ' ')
			buf->type[x] = _SPACE; 
		else if (buf->c[x] == '!')
			buf->type[x] = _EXCLAMATION_MARK; 
		else if (buf->c[x] == '\"')
			buf->type[x] = _DOUBLE_QUOTE; 
		else if (buf->c[x] == '#')
			buf->type[x] = _POUND; 
		else if (buf->c[x] == '$')
			buf->type[x] = _DOLLAR_SIGN; 
		else if (buf->c[x] == '%')
			buf->type[x] = _PORCENT_SIGN; 
		else if (buf->c[x] == '^')
			buf->type[x] = _AMPERSAND; 
		else if (buf->c[x] == '\'')
			buf->type[x] = _APOSTROPHE; 
		else if (buf->c[x] == '(')
			buf->type[x] = _ROUND_BRACKET_LEFT; 
		else if (buf->c[x] == ')')
			buf->type[x] = _ROUND_BRACKET_RIGHT; 
		else if (buf->c[x] == '*')
			buf->type[x] = _ASTERISK; 
		else if (buf->c[x] == '+')
			buf->type[x] = _PLUS_SIGN; 
		else if (buf->c[x] == ',')
			buf->type[x] = _COMMA; 
		else if (buf->c[x] == '-')
		{
			//buf->type[x] = _HYPHEN;
			buf->type[x] = _WORD;
		}
		else if (buf->c[x] == '.')
			buf->type[x] = _FULL_STOP; 
		else if (buf->c[x] == '/')
			buf->type[x] = _SLASH; 
		else if (ft_isdigit(buf->c[x]) == 1)
			buf->type[x] = _DIGIT; 
		else if (buf->c[x] == ':')
			buf->type[x] = _COLON; 
		else if (buf->c[x] == ';')
			buf->type[x] = _SEP; 
		else if (buf->c[x] == '<')
			buf->type[x] = _GUILLEMET_LEFT; 
		else if (buf->c[x] == '=')
			buf->type[x] = _EQUAL_SIGN; 
		else if (buf->c[x] == '>')
			buf->type[x] = _GUILLEMET_RIGHT; 
		else if (buf->c[x] == '?')
			buf->type[x] = _QUESTION_MARK; 
		else if (buf->c[x] == '@')
			buf->type[x] = _AT_SIGN; 
		else if (ft_isalpha(buf->c[x]) == 1)
			buf->type[x] = _ALPHA; 
		else if (buf->c[x] == '[')
			buf->type[x] = _SQUARE_BRACKET_LEFT; 
		else if (buf->c[x] == '\\')
			buf->type[x] = _BACKSLASH; 
		else if (buf->c[x] == ']')
			buf->type[x] = _SQUARE_BRACKET_RIGHT; 
		else if (buf->c[x] == '^')
			buf->type[x] = _CARET; 
		else if (buf->c[x] == '_')
			buf->type[x] = _UNDERSCORE; 
		else if (buf->c[x] == '`')
			buf->type[x] = _PRIME; 
		else if (buf->c[x] == '{')
			buf->type[x] = _CURLY_BRACKET_RIGHT; 
		else if (buf->c[x] == '|')
			buf->type[x] = _PIPE; 
		else if (buf->c[x] == '}')
			buf->type[x] = _CURLY_BRACKET_LEFT; 
		else if (buf->c[x] == '~')
			buf->type[x] = _TILDE; 
		else if (buf->c[x] == '\t' || buf->c[x] == '\v')
			buf->type[x] = _TAB; 
		else if (buf->c[x] == '\n')
			buf->type[x] = _NEW_LINE; 
		else
			buf->type[x] = _OTHER; 
		x++;
	}
	cut_quoting(buf);
	cut_commands(buf);
	creat_sep(buf, &base);
	ft_print_lchar(buf);
	print_base(base);
	exec_base(base, my_envp, history_first);
	return (0);
}
