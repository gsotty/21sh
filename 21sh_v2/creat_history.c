/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 08:32:20 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/17 16:29:24 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./vingt_et_un_sh.h"

static int	len_file_history()
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

char	**creat_history(t_history *history)
{
	char		**new_history;
	char		*ligne;
	int			fd;
	int			x;

	x = 0;
	if ((history->len = len_file_history()) == -1)
		return (NULL);
	if ((new_history = ft_memalloc(sizeof(char *) * (history->len + 2))) == NULL)
		return (NULL);
	history->len_malloc = history->len;
	if ((fd = open(PATH_HISTORY, O_RDWR | O_CREAT | O_APPEND, S_IRUSR |
					S_IWUSR)) == -1)
		return (NULL);
	while (x < history->len)
	{
		if (get_next_line(fd, &ligne) == -1)
			return (NULL);
		new_history[x] = ft_strdup(ligne);
		free(ligne);
		x++;
	}
	new_history[x] = NULL;
	close(fd);
	return (new_history);
}
