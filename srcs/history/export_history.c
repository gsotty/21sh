#include "../../include/history.h"

int		export_history(t_history *history, int error)
{
	int		fd;
	int		x;

	x = 0;
	if ((fd = open(PATH_HISTORY, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
		return (1);
	while (x <= history->len)
	{
		if (!(error == 1 && x == history->pos_buf))
		{
			write(fd, history->buf[x]->c, history->buf[x]->len);
			write(fd, "\n", 1);
		}
		free(history->buf[x]);
		x++;
	}
	free(history->buf);
	free(history->pos);
	close(fd);
	return (0);
}
