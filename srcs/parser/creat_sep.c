#include "../../include/parser.h"

static int	nbr_of_sep(t_lchar *buf, int x)
{
	int		nbr_sep;

	nbr_sep = 1;
	while (x < buf->len)
	{
		if (buf->type[x] == _SEP)
			nbr_sep++;
		x++;
	}
	return (nbr_sep);
}

int			creat_sep(t_lchar *buf, t_parser_shell *base)
{
	int		x;
	int		start_sep;
	int		nbr_sep;

	base->len = nbr_of_sep(buf, 0);
	if ((base->sep = ft_memalloc(sizeof(t_separateurs) *
					(base->len + 1))) == NULL)
		return (1);
	x = 0;
	nbr_sep = 0;
	start_sep = 0;
	while (1)
	{
		if (buf->len < x || buf->type[x] == _SEP)
		{
			creat_pipe(buf, start_sep, x, &base->sep[nbr_sep]);
			start_sep = x;
			nbr_sep++;
			if (buf->len < x)
				break ;
		}
		x++;
	}
	return (0);
}
