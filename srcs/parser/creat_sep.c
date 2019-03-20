#include "../../include/parser.h"

static int	nbr_of_sep(t_lchar *buf, int x, int end)
{
	int		nbr_sep;

	nbr_sep = 0;
	while (1)
	{
		if (buf->type[x] == _SEP)
			nbr_sep++;
		if (x >= end)
		{
			nbr_sep++;
			break ;
		}
		x++;
	}
	return (nbr_sep);
}

static int	copy_sep(t_lchar *buf, int x, int end, t_parser_shell *base, t_history *history)
{
	int		start_sep;
	int		nbr_sep;

	nbr_sep = 0;
	start_sep = x;
	while (1)
	{
		if (buf->type[x] == _SEP)
		{
			if (creat_pipe(buf, start_sep, (x - 1), &base->sep[nbr_sep], history) == 1)
				return (1);
			start_sep = x + 1;
			nbr_sep++;
		}
		if (x >= end)
		{
			if (creat_pipe(buf, start_sep, x, &base->sep[nbr_sep], history) == 1)
				return (1);
			break ;
		}
		x++;
	}
	return (0);
}

int			creat_sep(t_lchar *buf, t_parser_shell *base, t_history *history)
{
	base->len = nbr_of_sep(buf, 0, (buf->len - 1));
	if ((base->sep = ft_memalloc(sizeof(t_separateurs) *
					(base->len + 1))) == NULL)
		return (1);
	if (copy_sep(buf, 0, (buf->len - 1), base, history) == 1)
		return (1);
	return (0);
}
