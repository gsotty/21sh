#include "../../include/vingt_et_un_sh.h"
#include "../../include/lchar.h"

int				ft_freehistory(t_history *history)
{
	int		count;

	count = 0;
	while (count < history->malloc)
	{
		free(history->buf[count]->c);
		free(history->buf[count]->type);
		free(history->buf[count]);
		count++;
	}
	free(history->pos);
	free(history->buf);
	return (0);
}
