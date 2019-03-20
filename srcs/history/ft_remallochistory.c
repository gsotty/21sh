#include "../../include/vingt_et_un_sh.h"
#include "../../include/lchar.h"

int				ft_remallochistory(t_history *history)
{
	t_history	tmp_history;

	ft_historycpy(history, &tmp_history, 0);
	ft_freehistory(history);
	ft_historycpy(&tmp_history, history, REMALLOC_HISTORY);
	ft_freehistory(&tmp_history);
	return (0);
}
