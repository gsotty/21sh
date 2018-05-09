#include "../../include/lchar.h"
#include "../../include/parser.h"

int		parser(t_lchar *buf)
{
	int		x;

	x = 0;
	while (x < buf->len)
	{
		if (ft_isdigit(buf->c[x]) == 1)
			buf->type[x] = DIGIT;
	}
	return (0);
}
