#include "../../include/history.h"

int		export_history(t_history *history)
{
	int		fd;
	int		x;

	x = 0;
	if ((fd = open(PATH_HISTORY, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
		return (1);
	while (x < history->len_buf)
	{
		write(fd, history->buf[x], history->len[x]);
		write(fd, "\n", 1);
		free(history->buf[x]);
		x++;
	}
	free(history->buf);
	close(fd);
	return (0);
}
