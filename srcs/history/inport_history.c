/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inport_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:29:52 by gsotty            #+#    #+#             */
/*   Updated: 2019/04/04 14:51:50 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/history.h"
#include "../../include/parser.h"

static int		ft_nbr_line(void)
{
	int		fd;
	int		ret;
	int		count;
	char	*line;

	count = 0;
	if ((fd = open(PATH_HIST, O_RDONLY)) == -1)
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

static int		while_get_next_line(int fd, t_history *hist)
{
	int		x;
	int		ret;
	int		len;
	char	*line;

	x = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ret == -1)
			return (-1);
		if ((hist->buf[x] = ft_memalloc(sizeof(t_lchar) + 1)) == NULL)
			return (1);
		len = ft_strlen(line);
		hist->buf[x]->len = len;
		hist->pos[x] = 0;
		if ((hist->buf[x]->c = ft_memalloc((sizeof(char) * len) + 1)) == NULL)
			return (1);
		ft_memcpy(hist->buf[x]->c, line, len);
		if ((hist->buf[x]->type = ft_memalloc((sizeof(int) * len) + 1)) == NULL)
			return (1);
		ft_addtype(hist->buf[x], 0, hist->buf[x]->len);
		free(line);
		x++;
	}
	return (0);
}

static int		take_line(int fd, int len, t_history *history)
{
	close(fd);
	if ((fd = open(PATH_HIST, O_RDONLY)) == -1)
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

	if ((fd = open(PATH_HIST, O_RDONLY)) != -1)
	{
		if ((ret = take_line(fd, ft_nbr_line(), history)) == 1)
			return (1);
		if (ret == -1)
			return (-1);
	}
	else
	{
		if ((fd = open(PATH_HIST, O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR)) == -1)
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
