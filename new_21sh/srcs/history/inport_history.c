#include "../../include/history.h"

static int		nbr_line()
{
	int		fd;
	int		ret;
	int		cont;
	char	*line;

	cont = 0;
	if ((fd = open(PATH_HISTORY, O_RDONLY)) == -1)
		return (-1);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ret == -1)
			return (-1);
		free(line);
		cont++;
	}
	close(fd);
	return (cont);
}

static int		take_line(int fd, int len, t_history *history)
{
	int		cont;
	int		ret;
	int		len_arg;
	char	*line;

	if (len == -1)
		return (1);
	history->len_buf = len;
	history->malloc_buf = len;
	history->pos_buf = len;
	if ((history->len = ft_memalloc(sizeof(int) * (len + 2))) == NULL)
		return (1);
	if ((history->len_malloc = ft_memalloc(sizeof(int) * (len + 2))) == NULL)
		return (1);
	if ((history->pos = ft_memalloc(sizeof(int) * (len + 2))) == NULL)
		return (1);
	if ((history->buf = ft_memalloc(sizeof(char *) * (len + 2))) == NULL)
		return (1);
	cont = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ret == -1)
			return (1);
		len_arg = ft_strlen(line);
		history->len[cont] = len_arg;
		history->len_malloc[cont] = len_arg;
		history->pos[cont] = 0;
		if ((history->buf[cont] = ft_memalloc(sizeof(char) * (len_arg + 1))) == NULL)
			return (1);
		ft_memcpy(history->buf[cont], line, len_arg);
		history->buf[cont][len_arg] = '\0';
		free(line);
		cont++;
	}
	history->buf[cont] = NULL;
	history->len[cont] = 0;
	history->len_malloc[cont] = 0;
	history->pos[cont] = 0;
	return (0);
}

int			inport_history(t_history *history)
{
	int		fd;

	if ((fd = open(PATH_HISTORY, O_RDONLY)) != -1) // si il reussi c'est que le fichier existe
	{
		if ((take_line(fd, nbr_line(), history)) == 1)
			return (1);
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
