#include "../../include/history.h"
#include <stdio.h>

static int		ft_nbr_line()
{
	int		fd;
	int		ret;
	int		count;
	char	*line;

	count = 0;
	if ((fd = open(PATH_HISTORY, O_RDONLY)) == -1)
		return (-1);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		printf("bonjour N%d, ret = [%d], line = [%s]\n", count, ret, line);
		if (ret == -1)
			return (-1);
		free(line);
		count++;
	}
	close(fd);
	return (count);
}

static int		take_line(int len, t_history *history)
{
	int		fd;
	int		count;
	int		ret;
	int		len_arg;
	char	*line;

	if ((fd = open(PATH_HISTORY, O_RDONLY)) == -1)
		return (-1);
	if (len == -1)
		return (1);
	history->len_buf = len - 1;
	history->malloc_buf = len - 1;
	history->pos_buf = len - 1;
	if ((history->len = ft_memalloc(sizeof(int) * (len + 1))) == NULL)
		return (1);
	if ((history->len_malloc = ft_memalloc(sizeof(int) * (len + 1))) == NULL)
		return (1);
	if ((history->pos = ft_memalloc(sizeof(int) * (len + 1))) == NULL)
		return (1);
	if ((history->buf = ft_memalloc(sizeof(char *) * (len + 1))) == NULL)
		return (1);
	count = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		len_arg = ft_strlen(line);
		history->len[count] = len_arg;
		history->len_malloc[count] = len_arg;
		history->pos[count] = 0;
		if ((history->buf[count] = ft_memalloc(sizeof(char) * (len_arg + 1))) == NULL)
			return (1);
		ft_memcpy(history->buf[count], line, len_arg);
		free(line);
		count++;
	}
	close(fd);
	return (0);
}

#include <stdio.h>

int			inport_history(t_history *history)
{
	int		fd;
	int		ret;

	if ((fd = open(PATH_HISTORY, O_RDONLY)) != -1) // si il reussi c'est que le fichier existe
	{
		close(fd);
		ret = 0;
		if ((ret = take_line(ft_nbr_line(), history)) == 1)
			return (1);
		if (ret == -1)
			return (-1);
	}
	else // si nn le fichier n'existe pas
	{
		if ((fd = open(PATH_HISTORY, O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR)) == -1)
			return (1);
		history->len_buf = 0;
		history->malloc_buf = 0;
		history->pos_buf = 0;
	}
	close(fd);

	printf("\nimport history: %d, %d, %d\n", history->len_buf, history->malloc_buf, history->pos_buf);
	int w = 0;
	while (history->len_buf >= w)
	{
		printf("%d, %d, %d, %d, %s\n", w, history->len[w], history->len_malloc[w], history->pos[w], history->buf[w]);
		w++;
	}
	printf("exit import\n\n");

	return (0);
}
