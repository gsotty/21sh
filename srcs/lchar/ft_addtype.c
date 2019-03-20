#include "../../include/history.h"
#include "../../include/parser.h"

static int		ft_isspace(int c)
{
	if (c == 32 || c == 9 || c == 11)
		return (1);
	return (0);
}

static int		ft_isnoprint(int c)
{
	if ((c >= 0 && c <= 3) || (c >= 5 && c <= 8) || (c >= 12 && c <= 31))
		return (1);
	return (0);
}

int				ft_addtype(t_lchar *buf, int start, int end)
{
	int		x;

	x = start;
	while (x < end)
	{
		if (ft_isalpha(buf->c[x]) == 1)
			buf->type[x] = _ALPHA;
		else if (ft_isdigit(buf->c[x]) == 1)
			buf->type[x] = _DIGIT;
		else if (ft_isspace(buf->c[x]) == 1)
			buf->type[x] = _SPACE;
		else if (buf->c[x] == 4)
			buf->type[x] = _EOT;
		else if (buf->c[x] == 10)
			buf->type[x] = _NEW_LINE;
		else if (ft_isnoprint(buf->c[x]) == 1)
			buf->type[x] = _NOPRINT;
		else
			buf->type[x] = (int)buf->c[x];
		x++;
	}
	return (0);
}

