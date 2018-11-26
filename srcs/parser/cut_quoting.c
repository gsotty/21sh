#include "../../include/parser.h"

static int	add_type(int *x, t_lchar *buf, int limit)
{
	buf->type[*x] = _DEL;
	if ((*x + 1) < buf->len)
	{
		*x = *x + 1;
		while (*x < buf->len)
		{
			buf->type[*x] = _WORD;
			if (buf->type[*x] == limit)
			{
				buf->type[*x] = _DEL;
				break ;
			}
			*x = *x + 1;
		}
	}
	return (0);
}

static int	while_cut(int *x, t_lchar *buf)
{
	if (buf->type[*x] == _APOSTROPHE)
		add_type(x, buf, _APOSTROPHE);
	else if (buf->type[*x] == _DOUBLE_QUOTE)
		add_type(x, buf, _DOUBLE_QUOTE);
	else if (buf->type[*x] == _BACKSLASH)
	{
		if ((*x + 1) < buf->len)
		{
			buf->type[*x + 1] = _WORD;
		}
	}
	if (buf->type[*x] == _ALPHA)
		buf->type[*x] = _WORD;
	return (0);
}

int		cut_quoting(t_lchar *buf)
{
	int		x;

	x = 0;
	while (x < buf->len)
	{
		while_cut(&x, buf);
		x++;
	}
	return (0);
}

