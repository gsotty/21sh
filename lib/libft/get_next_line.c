/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git_next_line_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 12:11:12 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/18 11:52:53 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"
#include <unistd.h>
#include <stdlib.h>

int		buffer_to_stock(int fd, int len_stock, char **stock, int *bytes_read)
{
	char	*buffer;
	char	*tmp;

	buffer = (char*)malloc(sizeof(char) * BUFF_SIZE + 1);
	if (buffer == NULL)
		return (0);
	*bytes_read = read(fd, buffer, BUFF_SIZE);
	if (*bytes_read == -1)
	{
		free(buffer);
		return (0);
	}
	else if (*bytes_read == 0)
	{
		free(buffer);
		return (1);
	}
	buffer[*bytes_read] = '\0';
	if ((tmp = ft_memalloc(sizeof(char) * (len_stock + BUFF_SIZE + 1))) == NULL)
		return (0);
	ft_memcpy(tmp, *stock, len_stock);
	free(*stock);
	ft_memcpy(tmp + len_stock, buffer, BUFF_SIZE);
	free(buffer);
	*stock = tmp;
	return (1);
}

#include <stdio.h>

void	cut_stock(char **stock, char *str)
{
	char		*tmp;

	tmp = ft_strdup(str + 1);
	free(*stock);
	*stock = tmp;
}

int		file_end(char **line, char **stock)
{
	if (ft_strlen(*stock))
	{
		*line = ft_strdup(*stock);
		free(*stock);
		return (1);
	}
	return (0);
}

int		error_handling(char **stock)
{
	free(*stock);
	return (-1);
}

int		get_next_line(const int fd, char **line)
{
	static char		*stock = NULL;
	char			*str;
	int				bytes_read;
	int				len_stock;

	if (fd < 0 || BUFF_SIZE < 0)
		return (-1);
	if (!(stock))
		stock = ft_strnew(0);
	while (!(ft_strchr(stock, '\n')))
	{
		len_stock = ft_strlen(stock);
		if (!(buffer_to_stock(fd, len_stock, &stock, &bytes_read)))
			return (error_handling(&stock));
		if (bytes_read == 0)
			return (file_end(line, &stock));
	}
	str = ft_strchr(stock, '\n');
	printf("test: [%s], [%ld]\n", stock, str - stock);
	*line = ft_strsub(stock, 0, str - stock);
	cut_stock(&stock, str);
	return (1);
}
