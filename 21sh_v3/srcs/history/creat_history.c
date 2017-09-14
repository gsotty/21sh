/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 08:32:20 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/13 10:55:29 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static int			len_file_history(void)
{
	int			x;
	int			fd;
	int			ret;
	char		*ligne;

	x = 0;
	if ((fd = open(PATH_HISTORY, O_RDONLY)) == -1)
		return (0);
	while ((ret = get_next_line(fd, &ligne)) > 0)
	{
		free(ligne);
		if (ret == -1)
			return (-1);
		x++;
	}
	close(fd);
	return (x);
}

static t_lchar		*char_to_lchar(const char *str)
{
	t_lchar		*ret;
	int			i;

	if ((ret = ft_memalloc(sizeof(t_lchar) * (ft_strlen(str) + 1))) == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		ret[i].c = str[i];
		ret[i].type = 0;
		i++;
	}
	ret[i].c = '\0';
	return (ret);
}

static int			creat_history_loop(int fd, t_lchar **new_history, int x)
{
	char		*ligne;
	int			ret;

	if ((ret = get_next_line(fd, &ligne)) == -1)
		return (1);
	new_history[x] = char_to_lchar(ligne);
	free(ligne);
	return (0);
}

t_lchar				**creat_history(t_history *history)
{
	t_lchar		**new_history;
	int			fd;
	int			x;

	x = 0;
	if ((history->len = len_file_history()) == -1)
		return (NULL);
	if ((new_history = ft_memalloc(sizeof(t_lchar *) *
					(history->len + 2))) == NULL)
		return (NULL);
	history->len_malloc = history->len;
	if ((fd = open(PATH_HISTORY, O_RDWR | O_CREAT | O_APPEND, S_IRUSR |
					S_IWUSR)) == -1)
		return (NULL);
	while (x < history->len)
	{
		creat_history_loop(fd, new_history, x);
		x++;
	}
	new_history[x] = NULL;
	close(fd);
	return (new_history);
}
