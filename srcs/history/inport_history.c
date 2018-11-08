#include "../../include/history.h"
#include <stdio.h>

static int		nbr_line()
{
	int		fd;
	int		ret;
	int		count;
	char	*line;

	count = 0;
	if ((fd = open(PATH_HISTORY, O_RDONLY)) == -1)
		return (-1);
	while ((ret = get_next_line(fd, &line)) > 0 && count++)
	{
		if (ret == -1)
			return (-1);
		free(line);
	}
	close(fd);
	return (count);
}

static int		take_line(int fd, int len, t_history *history)
{
	int		count;
	int		ret;
	int		len_arg;
	char	*line;

	if (len == -1)
		return (1);
	history->len_buf = len;
	history->malloc_buf = len;
	history->pos_buf = len;
	if ((history->len = ft_memalloc(sizeof(int) * len)) == NULL)
		return (1);
	if ((history->len_malloc = ft_memalloc(sizeof(int) * len)) == NULL)
		return (1);
	if ((history->pos = ft_memalloc(sizeof(int) * len)) == NULL)
		return (1);
	if ((history->buf = ft_memalloc(sizeof(char *) * len)) == NULL)
		return (1);
	count = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
	while ((ret = get_next_line(fd, &line)) > 0)
		if (ret == -1)
			return (1);
		len_arg = ft_strlen(line);
		history->len[count] = len_arg;
		history->len_malloc[count] = len_arg;
		history->pos[count] = 0;
		if ((history->buf[count] = ft_memalloc(sizeof(char) * len_arg)) == NULL)
			return (1);
		ft_memcpy(history->buf[count], line, len_arg);
		history->buf[count][len_arg] = '\0';
		free(line);
		count++;
	}
	history->buf[count] = NULL;
	history->len[count] = 0;
	history->len_malloc[count] = 0;
	history->pos[count] = 0;
	return (0);
}

#include <stdio.h>

int			inport_history(t_history *history)
{
	int		fd;

	if ((fd = open(PATH_HISTORY, O_RDONLY)) != -1) // si il reussi c'est que le fichier existe
	{
		if ((take_line(fd, nbr_line(), history)) == 1)
			return (1);
		printf("%d, %d, %d\n", history->len_buf, history->malloc_buf, history->pos_buf);
		int w = 0;
		while (history->len_buf > w)
		{
			printf("%d, %d, %d, %d, %s\n", w, history->len[w], history->len_malloc[w], history->pos[w], history->buf[w]);
			w++;
		}
	}
	else // si nn le fichier n'existe pas
	{
		if ((fd = open(PATH_HISTORY, O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR)) == -1)
			return (1);
		if ((history->buf = ft_memalloc(sizeof(char *) + 2)) == NULL)
			return (1);
	}
	close(fd);
	return (0);
}
