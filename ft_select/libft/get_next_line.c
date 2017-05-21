/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 16:05:54 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/31 13:55:23 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static void		putback(t_file *begin, t_file *new)
{
	t_file *tmp;

	if (!(begin))
	{
		begin = new;
	}
	else
	{
		tmp = begin;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static t_file	*newf(int fd, t_file *begin)
{
	t_file	*new;

	if (!(new = (t_file*)malloc(sizeof(*new))))
		return (NULL);
	new->str = ft_strnew(0);
	new->fd = fd;
	new->next = NULL;
	putback(begin, new);
	return (new);
}

static t_file	*sel(t_file *begin, int fd)
{
	t_file	*tmp;

	tmp = begin;
	while (tmp != NULL)
	{
		if (tmp->fd == fd)
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (newf(fd, begin));
}

static int		get_str(t_file *tmp, char **line)
{
	char	*eol;

	eol = ft_strchr(tmp->str, '\n');
	if (eol)
	{
		eol[0] = '\0';
		*line = ft_strdup(tmp->str);
		tmp->str = ft_strncpy(tmp->str, &eol[1], ft_strlen(&eol[1]) + 1);
		return (1);
	}
	if (ft_strlen(tmp->str) > 0)
	{
		*line = ft_strdup(tmp->str);
		*tmp->str = '\0';
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_file	*begin = NULL;
	char			buff[BUFF_SIZE + 1];
	t_file			*tmp;
	int				ret;
	char			*tmp_str;

	if (!begin)
		begin = newf(fd, begin);
	tmp = sel(begin, fd);
	if (tmp->fd < 0 || !(tmp->str) || !line || BUFF_SIZE <= 0)
		return (-1);
	while (!ft_strchr(tmp->str, '\n'))
	{
		if ((ret = read(tmp->fd, buff, BUFF_SIZE)) == -1)
			return (-1);
		buff[ret] = '\0';
		if (ret == 0)
			return (get_str(tmp, line));
		tmp_str = ft_strjoin(tmp->str, buff);
		free(tmp->str);
		tmp->str = tmp_str;
	}
	return (get_str(tmp, line));
}
