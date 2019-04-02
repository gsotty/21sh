#include "../../include/history.h"
#include "../../include/parser.h"

static int		ft_nbr_line(void)
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
		if (ret == -1)
			return (-1);
		free(line);
		count++;
	}
	close(fd);
	return (count);
}


static int		while_get_next_line(int fd, t_history *history)
{
	int		ret;
	int		count;
	int		len_arg;
	char	*line;

	count = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ret == -1)
			return (-1);
		if ((history->buf[count] = ft_memalloc(sizeof(t_lchar) + 1)) == NULL)
			return (1);
		len_arg = ft_strlen(line);
		history->buf[count]->len = len_arg;
		history->pos[count] = 0;
		if ((history->buf[count]->c = ft_memalloc((sizeof(char) *
							len_arg) + 1)) == NULL)
			return (1);
		ft_memcpy(history->buf[count]->c, line, len_arg);
		if ((history->buf[count]->type = ft_memalloc((sizeof(int) *
							len_arg) + 1)) == NULL)
			return (1);
		ft_addtype(history->buf[count], 0, history->buf[count]->len);
		free(line);
		count++;
	}
	return (0);
}

static int		take_line(int len, t_history *history)
{
	int		fd;

	if ((fd = open(PATH_HISTORY, O_RDONLY)) == -1)
		return (-1);
	if (len == -1)
		return (1);
	history->len = len - 1;
	history->malloc = len - 1;
	history->pos_buf = len - 1;
	if ((history->pos = ft_memalloc(sizeof(int) * (len))) == NULL)
		return (1);
	if ((history->buf = ft_memalloc(sizeof(t_lchar *) * (len))) == NULL)
		return (1);
	while_get_next_line(fd, history);
	close(fd);
	return (0);
}

int				inport_history(t_history *history)
{
	int		fd;
	int		ret;

	if ((fd = open(PATH_HISTORY, O_RDONLY)) != -1)
	{
		close(fd);
		ret = 0;
		if ((ret = take_line(ft_nbr_line(), history)) == 1)
			return (1);
		if (ret == -1)
			return (-1);
	}
	else
	{
		if ((fd = open(PATH_HISTORY, O_CREAT | O_RDONLY,
						S_IRUSR | S_IWUSR)) == -1)
			return (1);
		history->len = 0;
		history->malloc = 0;
		history->pos_buf = 0;
		if ((history->pos = ft_memalloc(sizeof(int))) == NULL)
			return (1);
		if ((history->buf = ft_memalloc(sizeof(t_lchar *))) == NULL)
			return (1);
	}
	close(fd);
	return (0);
}
