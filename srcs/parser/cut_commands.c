#include "../../include/parser.h"

static int	while_word(int *x, int *first_cmd, int *is_file_name, t_lchar *buf)
{
	while (buf->type[*x] == _ALPHA || buf->type[*x] == _WORD)
	{
		if (*first_cmd == 0 && *is_file_name == 0)
			buf->type[*x] = _WORD;
		else if (*first_cmd == 1 && *is_file_name == 0)
			buf->type[*x] = _WORD;
		else if (*first_cmd == 1 && *is_file_name == 1)
			buf->type[*x] = _FILE_NAME;
		*x = *x + 1;
		if ((buf->type[*x] != _ALPHA && buf->type[*x] != _WORD) && *first_cmd == 0)
			*first_cmd = 1;
		else if ((buf->type[*x] != _ALPHA && buf->type[*x] != _WORD) && *is_file_name == 1)
			*is_file_name = 0;
	}
	return (0);
}

int		cut_commands(t_lchar *buf)
{
	int		x;
	int		first_cmd;
	int		is_file_name;

	x = 0;
	first_cmd = 0;
	is_file_name = 0;
	while (x < buf->len)
	{
		while_word(&x, &first_cmd, &is_file_name, buf);
		while ((buf->type[x] == _ALPHA || buf->type[x] == _WORD) && first_cmd == 1)
		{
			buf->type[x] = _ARGV;
			x++;
		}
		if (buf->type[x] == _GUILLEMET_RIGHT)
		{
			if (buf->type[x - 1] == _AMPERSAND)
			{
				buf->type[x - 1] = _SPACE;
				buf->type[x] = _ROUTERR;
			}
			else if (buf->type[x + 1] == _AMPERSAND)
			{
				buf->type[x - 1] = _SPACE;
				buf->type[x] = _ROUTERR;
			}
			else if (buf->type[x + 1] == _GUILLEMET_RIGHT)
			{
				buf->type[x] = _APPROUT;
				buf->type[x + 1] = _SPACE;
			}
			else
			{
				buf->type[x] = _ROUT;
			}
			is_file_name = 1;
		}
		else if (buf->type[x] == _GUILLEMET_LEFT)
		{
			if (buf->type[x + 1] == _AMPERSAND)
			{
				buf->type[x - 1] = _SPACE;
				buf->type[x] = _ROUTERR;
			}
			else if (buf->type[x + 1] == _GUILLEMET_LEFT)
			{
				buf->type[x] = _HEREDOC;
				buf->type[x + 1] = _SPACE;
			}
			else
			{
				buf->type[x] = _RINT;
			}
			is_file_name = 1;
		}
		if (buf->type[x] == _PIPE || buf->type[x] == _SEP)
		{
			first_cmd = 0;
			is_file_name = 0;
		}
		x++;
	}
	return (0);
}

