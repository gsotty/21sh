#include "../../include/parser.h"
#include "../../include/execute.h"

#include <stdio.h>

void	ft_print_lchar(t_lchar *buf)
{
	int		x;
	char	*nbr;

	x = 0;
	while (x < buf->len)
	{
		write(1, "buf = [", 7);
		nbr = ft_itoa(x);
		write(1, nbr, ft_strlen(nbr));
		free(nbr);
		write(1, "], [", 4);
		write(1, buf->c + x, 1);
		write(1, "], [", 4);
		write(1, which_define(buf->type[x]),
				ft_strlen(which_define(buf->type[x])));
		write(1, "]\n", 2);
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
	write(1, "len sep [", 9);
	nbr = ft_itoa(base.len);
	write(1, nbr, ft_strlen(nbr));
	free(nbr);
	write(1, "]\n", 2);
	while (x < base.len)
	{
		write(1, "	sep [", 6);
		nbr = ft_itoa(x);
		write(1, nbr, ft_strlen(nbr));
		free(nbr);
		write(1, "]\n", 2);
		write(1, "	len pipe [", 11);
		nbr = ft_itoa(base.sep[x].len);
		write(1, nbr, ft_strlen(nbr));
		free(nbr);
		write(1, "]\n", 2);
		y = 0;
		while (y < base.sep[x].len)
		{
			write(1, "		pipe [", 8);
			nbr = ft_itoa(y);
			write(1, nbr, ft_strlen(nbr));
			free(nbr);
			write(1, "]\n", 2);
			write(1, "		len cmd [", 11);
			nbr = ft_itoa(base.sep[x].pipel[y].argc);
			write(1, nbr, ft_strlen(nbr));
			free(nbr);
			write(1, "]\n", 2);
			z = 0;
			a = 0;
			if (base.sep[x].pipel[y].argc == 0 && x != (base.len - 1))
			{
				write(2, "erreur parser\n", 14);
			}
			while (z < base.sep[x].pipel[y].argc)
			{
				write(1, "			cmp [", 9);
				nbr = ft_itoa(z);
				write(1, nbr, ft_strlen(nbr));
				free(nbr);
				write(1, "]\n", 2);
				write(1, "				argv [", 10);
				write(1, base.sep[x].pipel[y].argv[z],
						ft_strlen(base.sep[x].pipel[y].argv[z]));
				write(1, "]\n", 2);
				z++;
			}
			write(1, "		len redir [", 13);
			nbr = ft_itoa(base.sep[x].pipel[y].len);
			write(1, nbr, ft_strlen(nbr));
			free(nbr);
			write(1, "]\n", 2);
			while (a < base.sep[x].pipel[y].len)
			{
				write(1, "			redir [", 10);
				nbr = ft_itoa(a);
				write(1, nbr, ft_strlen(nbr));
				free(nbr);
				write(1, "]\n", 2);
				write(1, "				type [", 10);
				write(1, which_define(base.sep[x].pipel[y].redir[a].type),
						ft_strlen(which_define(
								base.sep[x].pipel[y].redir[a].type)));
				write(1, "]\n", 2);
				write(1, "				fd_int [", 12);
				nbr = ft_itoa(base.sep[x].pipel[y].redir[a].fd_int);
				write(1, nbr, ft_strlen(nbr));
				free(nbr);
				write(1, "]\n", 2);
				write(1, "				file_int [", 14);
				if (base.sep[x].pipel[y].redir[a].file_int == NULL)
					write(1, "(NULL)", 6);
				else
					write(1, base.sep[x].pipel[y].redir[a].file_int,
							ft_strlen(base.sep[x].pipel[y].redir[a].file_int));
				write(1, "]\n", 2);
				write(1, "				fd_out [", 12);
				nbr = ft_itoa(base.sep[x].pipel[y].redir[a].fd_out);
				write(1, nbr, ft_strlen(nbr));
				free(nbr);
				write(1, "]\n", 2);
				write(1, "				file_out [", 14);
				if (base.sep[x].pipel[y].redir[a].file_out == NULL)
					write(1, "(NULL)", 6);
				else
					write(1, base.sep[x].pipel[y].redir[a].file_out,
							ft_strlen(base.sep[x].pipel[y].redir[a].file_out));
				write(1, "]\n", 2);
				write(1, "				len_here [", 14);
				nbr = ft_itoa(base.sep[x].pipel[y].redir[a].len_heredoc);
				write(1, nbr, ft_strlen(nbr));
				free(nbr);
				write(1, "]\n", 2);
				write(1, "				here [", 10);
				if (base.sep[x].pipel[y].redir[a].heredoc == NULL)
					write(1, "(NULL)", 6);
				else
					write(1, base.sep[x].pipel[y].redir[a].heredoc,
							ft_strlen(base.sep[x].pipel[y].redir[a].heredoc));
				write(1, "]\n", 2);
				a++;
			}
			y++;
		}
		x++;
	}
}

void	free_base(t_parser_shell base)
{
	int		x;
	int		y;
	int		z;
	int		a;

	x = 0;
	while (x < base.len)
	{
		y = 0;
		while (y < base.sep[x].len)
		{
			z = 0;
			a = 0;
			while (z < base.sep[x].pipel[y].argc)
			{
				free(base.sep[x].pipel[y].argv[z]);
				z++;
			}
			free(base.sep[x].pipel[y].argv);
			while (a < base.sep[x].pipel[y].len)
			{
				if (base.sep[x].pipel[y].redir[a].file_int != NULL)
					free(base.sep[x].pipel[y].redir[a].file_int);
				if (base.sep[x].pipel[y].redir[a].file_out != NULL)
					free(base.sep[x].pipel[y].redir[a].file_out);
				if (base.sep[x].pipel[y].redir[a].heredoc != NULL)
					free(base.sep[x].pipel[y].redir[a].heredoc);
				a++;
			}
			free(base.sep[x].pipel[y].redir);
			y++;
		}
		free(base.sep[x].pipel);
		x++;
	}
	free(base.sep);
}

int		parser(t_lchar *buf, char ***my_envp, t_history *history_first)
{
	int				x;
	t_parser_shell	base;

	x = 0;
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
		{
			//buf->type[x] = _EQUAL_SIGN;
			buf->type[x] = _WORD;
		}
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
	free_base(base);
	return (0);
}
