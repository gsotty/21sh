#include "../../include/vingt_et_un_sh.h"
#include "../../include/lchar.h"

t_history		*ft_historycpy(t_history *history_src,
		t_history *history_dest, int n)
{
	int			count;

	history_dest->len = history_src->len + n;
	history_dest->malloc = history_src->len + n;
	history_dest->pos_buf = history_src->pos_buf;
	if ((history_dest->pos = ft_memalloc(sizeof(int) *
					(history_dest->malloc + 1))) == NULL)
		return (NULL);
	if ((history_dest->buf = ft_memalloc(sizeof(t_lchar *) *
					(history_dest->malloc + 1))) == NULL)
		return (NULL);
	count = 0;
	while (count <= history_dest->malloc)
	{
		history_dest->pos[count] = 0;
		if ((history_dest->buf[count] = ft_memalloc(sizeof(t_lchar) + 1)) == NULL)
			return (NULL);
		if (count <= history_src->len)
		{
			history_dest->pos[count] = history_src->pos[count];
			history_dest->buf[count] = ft_lchardup(history_dest->buf[count],
					history_src->buf[count], 0);
		}
		else
		{
			history_dest->pos[count] = 0;
			if ((history_dest->buf[count]->c =
						ft_memalloc(sizeof(char) + 1)) == NULL)
				return (NULL);
			if ((history_dest->buf[count]->type =
						ft_memalloc(sizeof(int) + 1)) == NULL)
				return (NULL);
		}
		count++;
	}
	return (history_dest);
}
