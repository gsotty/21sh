#include "../../include/parser.h"
#include "../../include/execute.h"
#include <limits.h>

#include <stdio.h>

char	*token[] = {"&&", "||", ";;", "<<-", "<<", ">>", "<&", ">&", "<>", ">|",
	"<", ">", "|", ";", NULL};


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

static t_typecmd	*ft_typecmddup(t_typecmd *dest, t_lchar *src)
{
	int		x;

	dest->len = src->len;
	if ((dest->c = ft_memalloc(sizeof(char) * (dest->len + 1))) == NULL)
		return (NULL);
	if ((dest->type = ft_memalloc(sizeof(int) * (dest->len + 1))) == NULL)
		return (NULL);
	x = 0;
	while (x < dest->len)
	{
		dest->c[x] = src->c[x];
		dest->type[x] = src->type[x];
		x++;
	}
	return (dest);
}

static int	ft_onlydigit(int *type, int len)
{
	int		x;

	x = 0;
	while (x < len && type[x] == _DIGIT)
		x++;
	if (x == len)
		return (1);
	return (0);
}

int		ft_onlyspace(int *type, int len)
{
	int		x;

	x = 0;
	while (x < len && (type[x] == _SPACE || type[x] == _NEW_LINE))
		x++;
	if (x == len)
		return (1);
	return (0);
}

int		ft_addvalue_redir(t_typecmd *exec_struct, t_lchar **tab, int count_cmd, int maybe_fd, int type)
{
	if ((ft_typecmddup(exec_struct, tab[count_cmd])) == NULL)
		return (1);
	exec_struct->type_cmd = type;
	if ((exec_struct->file = ft_memalloc(sizeof(t_lchar))) == NULL)
		return (1);
	if (maybe_fd > -1)
		exec_struct->l_fd = ft_atoi_redir(tab[maybe_fd]->c, tab[maybe_fd]->len);
	else
	{
		exec_struct->l_fd = -1;
		if (type == _RINT || type == _HEREDOC || type == _DUPINT ||
				type == _RRDWR)
			exec_struct->l_fd = 0;
		else if (type == _ROUT || type == _APPROUT || type == _DUPOUT)
			exec_struct->l_fd = 1;
	}
	return (0);
}

int		ft_addvalue_cmd(t_typecmd ****exec_struct, int sep, int pipe, t_lchar **tab,
		int start_cmd, int count_pipe, t_history *history)
{
	char	*nbr;
	int		cmd;
	int		count_cmd;
	int		after_redir;
	int		maybe_fd;

	(void)history;
	cmd = 0;
	after_redir = -1;
	maybe_fd = -1;
	count_cmd = start_cmd;
	while (tab[count_cmd] != NULL && count_cmd < count_pipe)
	{
		if (ft_strmatch(tab[count_cmd]->c, "<") == 1)
		{
			if ((exec_struct[sep][pipe][cmd] =
						ft_memalloc(sizeof(t_typecmd))) == NULL)
				return (1);
			if ((ft_addvalue_redir(exec_struct[sep][pipe][cmd], tab, count_cmd,
							maybe_fd, _RINT)) == 1)
				return (1);
			after_redir = count_cmd;
			maybe_fd = -1;
			count_cmd++;
		}
		else if (ft_strmatch(tab[count_cmd]->c, ">") == 1)
		{
			if ((exec_struct[sep][pipe][cmd] =
						ft_memalloc(sizeof(t_typecmd))) == NULL)
				return (1);
			if ((ft_addvalue_redir(exec_struct[sep][pipe][cmd], tab, count_cmd,
							maybe_fd, _ROUT)) == 1)
				return (1);
			after_redir = count_cmd;
			maybe_fd = -1;
			count_cmd++;
		}
		else if (ft_strmatch(tab[count_cmd]->c, ">|") == 1)
		{
			if ((exec_struct[sep][pipe][cmd] =
						ft_memalloc(sizeof(t_typecmd))) == NULL)
				return (1);
			if ((ft_addvalue_redir(exec_struct[sep][pipe][cmd], tab, count_cmd,
							maybe_fd, _ROUT)) == 1)
				return (1);
			after_redir = count_cmd;
			maybe_fd = -1;
			count_cmd++;
		}
		else if (ft_strmatch(tab[count_cmd]->c, "<<-") == 1)
		{
			if ((exec_struct[sep][pipe][cmd] =
						ft_memalloc(sizeof(t_typecmd))) == NULL)
				return (1);
			if ((ft_addvalue_redir(exec_struct[sep][pipe][cmd], tab, count_cmd,
							maybe_fd, _HEREDOC)) == 1)
				return (1);
			after_redir = count_cmd;
			maybe_fd = -1;
			count_cmd++;
		}
		else if (ft_strmatch(tab[count_cmd]->c, "<<") == 1)
		{
			if ((exec_struct[sep][pipe][cmd] =
						ft_memalloc(sizeof(t_typecmd))) == NULL)
				return (1);
			if ((ft_addvalue_redir(exec_struct[sep][pipe][cmd], tab, count_cmd,
							maybe_fd, _HEREDOC)) == 1)
				return (1);
			after_redir = count_cmd;
			maybe_fd = -1;
			count_cmd++;
		}
		else if (ft_strmatch(tab[count_cmd]->c, ">>") == 1)
		{
			if ((exec_struct[sep][pipe][cmd] =
						ft_memalloc(sizeof(t_typecmd))) == NULL)
				return (1);
			if ((ft_addvalue_redir(exec_struct[sep][pipe][cmd], tab, count_cmd,
							maybe_fd, _APPROUT)) == 1)
				return (1);
			after_redir = count_cmd;
			maybe_fd = -1;
			count_cmd++;
		}
		else if (ft_strmatch(tab[count_cmd]->c, ">&") == 1)
		{
			if ((exec_struct[sep][pipe][cmd] =
						ft_memalloc(sizeof(t_typecmd))) == NULL)
				return (1);
			if ((ft_addvalue_redir(exec_struct[sep][pipe][cmd], tab, count_cmd,
							maybe_fd, _DUPOUT)) == 1)
				return (1);
			after_redir = count_cmd;
			maybe_fd = -1;
			count_cmd++;
		}
		else if (ft_strmatch(tab[count_cmd]->c, "<&") == 1)
		{
			if ((exec_struct[sep][pipe][cmd] =
						ft_memalloc(sizeof(t_typecmd))) == NULL)
				return (1);
			if ((ft_addvalue_redir(exec_struct[sep][pipe][cmd], tab, count_cmd,
							maybe_fd, _DUPINT)) == 1)
				return (1);
			after_redir = count_cmd;
			maybe_fd = -1;
			count_cmd++;
		}
		else if (ft_strmatch(tab[count_cmd]->c, "<>") == 1)
		{
			if ((exec_struct[sep][pipe][cmd] =
						ft_memalloc(sizeof(t_typecmd))) == NULL)
				return (1);
			if ((ft_addvalue_redir(exec_struct[sep][pipe][cmd], tab, count_cmd,
							maybe_fd, _RRDWR)) == 1)
				return (1);
			after_redir = count_cmd;
			maybe_fd = -1;
			count_cmd++;
		}
		else if (ft_onlydigit(tab[count_cmd]->type, tab[count_cmd]->len) == 1)
		{
			if (after_redir > -1)
			{
				if (exec_struct[sep][pipe][cmd]->type_cmd == _DUPINT ||
						exec_struct[sep][pipe][cmd]->type_cmd == _DUPOUT)
				{
					exec_struct[sep][pipe][cmd]->r_fd =
						ft_atoi_redir(tab[count_cmd]->c, tab[count_cmd]->len);
					if (isatty(exec_struct[sep][pipe][cmd]->r_fd) == 1)
					{
						if (exec_struct[sep][pipe][cmd]->file->len == 1 &&
								exec_struct[sep][pipe][cmd]->file->c[0] == '-')
						if ((ft_lchardup(exec_struct[sep][pipe][cmd]->file, tab[count_cmd], 0)) == NULL)
							return (1);
					}
					else
					{
						write(2, "21sh: ", 6);
						nbr = ft_itoa(exec_struct[sep][pipe][cmd]->r_fd);
						write(2, nbr, ft_strlen(nbr));
						free(nbr);
						write(2, ": bad file descriptor\n", 22);
						return (1);
					}
				}
				else
				{
					if ((ft_lchardup(exec_struct[sep][pipe][cmd]->file, tab[count_cmd], 0)) == NULL)
						return (1);
				}
				after_redir = -1;
				cmd++;
			}
			else
			{
				maybe_fd = count_cmd;
			}
			count_cmd++;
		}
		else if (ft_onlyspace(tab[count_cmd]->type, tab[count_cmd]->len) == 1)
		{
			if (maybe_fd > -1)
			{
				if ((exec_struct[sep][pipe][cmd] = ft_memalloc(sizeof(t_typecmd))) == NULL)
					return (1);
				if ((ft_typecmddup(exec_struct[sep][pipe][cmd], tab[maybe_fd])) == NULL)
					return (1);
				exec_struct[sep][pipe][cmd]->type_cmd = _WORD;
				maybe_fd = -1;
				cmd++;
			}
			count_cmd++;
		}
		else
		{
			if (maybe_fd > -1)
			{
				if ((exec_struct[sep][pipe][cmd] = ft_memalloc(sizeof(t_typecmd))) == NULL)
					return (1);
				if ((ft_typecmddup(exec_struct[sep][pipe][cmd], tab[maybe_fd])) == NULL)
					return (1);
				exec_struct[sep][pipe][cmd]->type_cmd = _WORD;
				maybe_fd = -1;
				cmd++;
			}
			if (after_redir > -1)
			{
				if ((ft_lchardup(exec_struct[sep][pipe][cmd]->file, tab[count_cmd], 0)) == NULL)
					return (1);
				exec_struct[sep][pipe][cmd]->r_fd = -1;
				after_redir = -1;
				cmd++;
			}
			else
			{
				if ((exec_struct[sep][pipe][cmd] = ft_memalloc(sizeof(t_typecmd))) == NULL)
					return (1);
				if ((ft_typecmddup(exec_struct[sep][pipe][cmd], tab[count_cmd])) == NULL)
					return (1);
				exec_struct[sep][pipe][cmd]->type_cmd = _WORD;
				cmd++;
			}
			count_cmd++;
			if (tab[count_cmd] == NULL || count_cmd >= count_pipe)
				return (0);
		}
	}
	cmd++;
	return (0);
}

typedef struct		s_parser_count
{
	char			str[4];
	int				redir;
}					t_parser_count;

int		ft_nbrcmd(t_lchar **tab, int start_cmd, int count_pipe)
{
	int		cmd;
	int		count_cmd;
	int		after_redir;
	int		maybe_fd;
	int		if_redir;
	t_parser_count	redir[] = {
		{"<<-", _APPROUT},
		{"<<", _HEREDOC},
		{">>", _APPROUT},
		{"<&", _DUPINT},
		{">&", _DUPOUT},
		{"<>", _RRDWR},
		{">|", _ROUT},
		{"<", _RINT},
		{">", _ROUT}
	};

	cmd = 0;
	after_redir = 0;
	maybe_fd = 0;
	count_cmd = start_cmd;
	while (tab[count_cmd] != NULL && count_cmd < count_pipe)
	{
		if_redir = 0;
		while (if_redir < 9)
		{
			if (ft_strmatch(tab[count_cmd]->c,  redir[if_redir].str) == 1)
			{
				maybe_fd = 0;
				after_redir = 1;
				count_cmd++;
				break ;
			}
			if_redir++;
		}
		if (ft_onlydigit(tab[count_cmd]->type, tab[count_cmd]->len) == 1)
		{
			if (after_redir == 1)
			{
				after_redir = 0;
				cmd++;
			}
			else
				maybe_fd = 1;
			count_cmd++;
		}
		else if (ft_onlyspace(tab[count_cmd]->type, tab[count_cmd]->len) == 1)
		{
			if (maybe_fd == 1)
			{
				cmd++;
				maybe_fd = 0;
			}
			count_cmd++;
		}
		else
		{
			if (maybe_fd == 1)
			{
				cmd++;
				maybe_fd = 0;
			}
			if (after_redir == 1)
			{
				after_redir = 0;
				cmd++;
			}
			else
				cmd++;
			count_cmd++;
			if (tab[count_cmd] == NULL || count_cmd >= count_pipe)
				return (cmd);
		}
	}
	cmd++;
	return (cmd);
}

int		ft_addvalue_pipe(t_typecmd ****exec_struct, int sep, t_lchar **tab,
		int start_pipe, int count_sep, t_history *history)
{
	int		pipe;
	int		count_pipe;
	int		start_cmd;

	pipe = 0;
	start_cmd = start_pipe;
	count_pipe = start_pipe;
	while (tab[count_pipe] != NULL && count_pipe < count_sep)
	{
		if (ft_strmatch(tab[count_pipe]->c, "|") == 1)
		{
			if ((ft_addvalue_cmd(exec_struct, sep, pipe, tab, start_cmd,
							count_pipe - 1, history)) == 1)
				return (1);
			pipe++;
			count_pipe++;
			start_cmd = count_pipe;
			if (tab[count_pipe] == NULL || count_pipe >= count_sep)
				return (0);
		}
		else
			count_pipe++;
	}
	if ((ft_addvalue_cmd(exec_struct, sep, pipe, tab, start_cmd,
					count_pipe, history)) == 1)
		return (1);
	pipe++;
	return (0);
}

int		ft_nbrcmd_pipe(t_typecmd ****exec_struct, t_lenexec *lenexec, int sep,
		t_lchar **tab, int start_pipe, int count_sep)
{
	int		pipe;
	int		count_pipe;
	int		start_cmd;

	pipe = 0;
	start_cmd = start_pipe;
	count_pipe = start_pipe;
	while (tab[count_pipe] != NULL && count_pipe < count_sep)
	{
		if (ft_strmatch(tab[count_pipe]->c, "|") == 1)
		{
			lenexec->cmd[sep][pipe] = ft_nbrcmd(tab, start_cmd, count_pipe - 1);
			if ((exec_struct[sep][pipe] = ft_memalloc(sizeof(t_typecmd *) *
							(lenexec->cmd[sep][pipe] + 1))) == NULL)
				return (1);
			pipe++;
			count_pipe++;
			start_cmd = count_pipe;
			if (tab[count_pipe] == NULL || count_pipe >= count_sep)
				return (0);
		}
		else
			count_pipe++;
	}
	lenexec->cmd[sep][pipe] = ft_nbrcmd(tab, start_cmd, count_pipe);
	if ((exec_struct[sep][pipe] = ft_memalloc(sizeof(t_typecmd *) *
							(lenexec->cmd[sep][pipe] + 1))) == NULL)
		return (1);
	pipe++;
	return (0);
}

int		ft_nbrpipe(t_lchar **tab, int start_pipe, int count_sep)
{
	int		pipe;
	int		count_pipe;

	pipe = 0;
	count_pipe = start_pipe;
	while (tab[count_pipe] != NULL && count_pipe < count_sep)
	{
		if (ft_strmatch(tab[count_pipe]->c, "|") == 1)
		{
			pipe++;
			count_pipe++;
			if (tab[count_pipe] == NULL || count_pipe >= count_sep)
				return (pipe);
		}
		else
			count_pipe++;
	}
	pipe++;
	return (pipe);
}

int		ft_addvalue_sep(t_typecmd ****exec_struct, t_lchar **tab,
		t_history *history)
{
	int		sep;
	int		count_sep;
	int		start_pipe;

	sep = 0;
	count_sep = 0;
	start_pipe = 0;
	while (tab[count_sep] != NULL)
	{
		if (ft_strmatch(tab[count_sep]->c, ";") == 1)
		{
			if ((ft_addvalue_pipe(exec_struct, sep, tab, start_pipe,
							count_sep - 1, history)) == 1)
				return (1);
			sep++;
			count_sep++;
			start_pipe = count_sep;
			if (tab[count_sep] == NULL)
				return (0);
		}
		else
			count_sep++;
	}
	if ((ft_addvalue_pipe(exec_struct, sep, tab, start_pipe,
					count_sep, history)) == 1)
		return (1);
	sep++;
	return (0);
}

int		ft_nbrcmd_sep(t_typecmd ****exec_struct, t_lenexec *lenexec, t_lchar **tab)
{
	int		sep;
	int		count_sep;
	int		start_pipe;

	sep = 0;
	count_sep = 0;
	start_pipe = 0;
	while (tab[count_sep] != NULL)
	{
		if (ft_strmatch(tab[count_sep]->c, ";") == 1)
		{
			if (ft_nbrcmd_pipe(exec_struct, lenexec, sep, tab, start_pipe, count_sep - 1) == 1)
				return (1);
			sep++;
			count_sep++;
			start_pipe = count_sep;
			if (tab[count_sep] == NULL)
				return (0);
		}
		else
			count_sep++;
	}
	if (ft_nbrcmd_pipe(exec_struct, lenexec, sep, tab, start_pipe, count_sep) == 1)
		return (1);
	sep++;
	return (0);
}

int		ft_nbrpipe_sep(t_typecmd ****exec_struct,
		t_lenexec *lenexec, t_lchar **tab)
{
	int		sep;
	int		count_sep;
	int		start_pipe;

	sep = 0;
	count_sep = 0;
	start_pipe = 0;
	while (tab[count_sep] != NULL)
	{
		if (ft_strmatch(tab[count_sep]->c, ";") == 1)
		{
			lenexec->pipe[sep] = ft_nbrpipe(tab, start_pipe, count_sep - 1);
			if ((exec_struct[sep] = ft_memalloc(sizeof(t_typecmd **) *
							(lenexec->pipe[sep] + 1))) == NULL)
				return (1);
			lenexec->nbr_process += lenexec->pipe[sep];
			if ((lenexec->cmd[sep] = ft_memalloc(sizeof(int) *
							(lenexec->pipe[sep] + 1))) == NULL)
				return (1);
			sep++;
			count_sep++;
			start_pipe = count_sep;
			if (tab[count_sep] == NULL)
				return (0);
		}
		else
			count_sep++;
	}
	lenexec->pipe[sep] = ft_nbrpipe(tab, start_pipe, count_sep);
	if ((exec_struct[sep] = ft_memalloc(sizeof(t_typecmd **) *
						(lenexec->pipe[sep] + 1))) == NULL)
		return (1);
	lenexec->nbr_process += lenexec->pipe[sep];
	if ((lenexec->cmd[sep] = ft_memalloc(sizeof(int) *
					(lenexec->pipe[sep] + 1))) == NULL)
		return (1);
	sep++;
	exec_struct[sep] = NULL;
	return (0);
}

int		ft_nbrsep(t_lchar **tab)
{
	int		sep;
	int		count_sep;
	int		start_pipe;
	int		test;

	sep = 0;
	count_sep = 0;
	start_pipe = 0;
	while (tab[count_sep] != NULL)
	{
		if (ft_strmatch(tab[count_sep]->c, ";") == 1)
		{
			if (start_pipe == count_sep)
			{
				printf("error\n");
				return (-1);
			}
			test = start_pipe;
			while (test < count_sep)
			{
				test++;
			}
			count_sep++;
			start_pipe = count_sep;
			sep++;
			if (tab[count_sep] == NULL)
			{
				return (sep);
			}
		}
		else
			count_sep++;
	}
	test = start_pipe;
	while (test < count_sep)
	{
		test++;
	}
	sep++;
	return (sep);
}

int		parser(t_lchar *buf, t_history *history, t_envp *my_envp)
{
	t_parser_shell	base;

	(void)base;
	(void)my_envp;
	(void)history;

	t_lchar			**tab;

	tab = ft_lcharsplit(buf, token);

	t_lenexec		*lenexec;
	t_process		*process;
	t_typecmd		****exec_struct;

	if ((lenexec = ft_memalloc(sizeof(t_lenexec))) == NULL)
		return (1);
	if ((lenexec->sep = ft_nbrsep(tab)) == -1)
		return (1);
	if ((exec_struct = ft_memalloc(sizeof(t_typecmd ***) * (lenexec->sep + 1))) == NULL)
		return (1);
	if ((lenexec->pipe = ft_memalloc(sizeof(int) * (lenexec->sep + 1))) == NULL)
		return (1);
	if ((lenexec->cmd = ft_memalloc(sizeof(int *) * (lenexec->sep + 1))) == NULL)
		return (1);
	if ((ft_nbrpipe_sep(exec_struct, lenexec, tab)) == 1)
		return (1);
	if ((process = ft_memalloc(sizeof(t_process) * (lenexec->nbr_process + 1))) == NULL)
		return (1);
	if ((ft_nbrcmd_sep(exec_struct, lenexec, tab)) == 1)
		return (1);
	if ((ft_addvalue_sep(exec_struct, tab, history)) == 1)
		return (1);

	char	*nbr;
	int		x = 0;
	int		y = 0;
	int		z = 0;
	while (exec_struct[x] != NULL)
	{
		y = 0;
		printf("sep\n");
		while (exec_struct[x][y] != NULL)
		{
			z = 0;
			printf("pipe\n");
			while (exec_struct[x][y][z] != NULL)
			{
				printf("pipe[%d][%d][%d]->c = [%s]\n", x, y, z, exec_struct[x][y][z]->c);
				if (exec_struct[x][y][z]->type_cmd == _RINT ||
						exec_struct[x][y][z]->type_cmd == _HEREDOC ||
						exec_struct[x][y][z]->type_cmd == _DUPINT ||
						exec_struct[x][y][z]->type_cmd == _RRDWR ||
						exec_struct[x][y][z]->type_cmd == _ROUT ||
						exec_struct[x][y][z]->type_cmd == _APPROUT ||
						exec_struct[x][y][z]->type_cmd == _DUPOUT)
				{
					write(1, "	l_fd [", 7);
					nbr = ft_itoa(exec_struct[x][y][z]->l_fd);
					write(1, nbr, ft_strlen(nbr));
					free(nbr);
					write(1, "]\n", 2);
					write(1, "	r_fd [", 7);
					nbr = ft_itoa(exec_struct[x][y][z]->r_fd);
					write(1, nbr, ft_strlen(nbr));
					free(nbr);
					write(1, "]\n", 2);
					write(1, "	file [", 7);
					write(1, exec_struct[x][y][z]->file->c, exec_struct[x][y][z]->file->len);
					write(1, "]\n", 2);
				}
				z++;
			}
			y++;
		}
		x++;
	}

	exec_base(exec_struct, process, lenexec, my_envp, history);
	return (0);
}
