/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 18:06:32 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/20 12:23:55 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_select.h"

static int		struc_buf(t_buf *buf, int argc, char **argv)
{
	int		x;

	x = 1;
	if (!(buf->tab_arg = ft_memalloc(sizeof(char *) * argc)))
		return (-1);
	if (!(buf->nbr = ft_memalloc(sizeof(int) * argc)))
		return (-1);
	buf->argc = argc - 1;
	while (argv[x] != NULL)
	{
		buf->tab_arg[x - 1] = ft_strdup(argv[x]);
		x++;
	}
	return (0);
}

int				main(int argc, char **argv)
{
	t_buf	buf;

	if (argc == 1)
	{
		write(2, "ft_select: no argument\n", 23);
		return (-1);
	}
	if (prepare_term() == -1)
		return (-1);
	ft_memset(&buf, 0, sizeof(t_buf));
	if ((struc_buf(&buf, argc, argv)) == -1)
		return (-1);
	while (1)
		read_ft_select(&buf);
	reset_term();
	free_buf(&buf);
	return (1);
}
