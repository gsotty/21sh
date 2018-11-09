#include "../../include/history.h"

int		export_history(t_history *history)
{
//	int		fd;
//	int		x;

	#include <stdio.h>
	printf("\nexport history: %d, %d, %d\n", history->len_buf, history->malloc_buf, history->pos_buf);
	int q = 0;
	while (history->len_buf >= q)
	{
		printf("%d, %d, %d, %d, %s\n", q, history->len[q], history->len_malloc[q], history->pos[q], history->buf[q]);
		q++;
	}
	printf("exit export\n\n");
/*	x = 0;
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
*/	return (0);
}
