/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_bar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 11:47:45 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/19 14:45:57 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_select.h"

static void		struc_buf(t_buf *buf, char **tmp_tab, int *tmp_nbr)
{
	int		x;

	x = 0;
	if (!(buf->tab_arg = ft_memalloc(sizeof(char *) * buf->argc)))
		return ;
	ft_memset(buf->tab_arg, 0, sizeof(char *) * buf->argc);
	if (!(buf->nbr = ft_memalloc(sizeof(int) * buf->argc)))
		return ;
	ft_memset(buf->nbr, 0, sizeof(int) * buf->argc);
	while (tmp_tab[x] != NULL)
	{
		buf->tab_arg[x] = ft_strdup(tmp_tab[x]);
		buf->nbr[x] = tmp_nbr[x];
		free(tmp_tab[x]);
		x++;
	}
	free(tmp_nbr);
	free(tmp_tab);
	if (buf->pos > 0)
		buf->pos--;
	buf->argc = buf->argc - 1;
}

void			delete_bar(t_buf *buf)
{
	int		x;
	int		y;
	int		*tmp_nbr;
	char	**tmp_tab;

	x = -1;
	y = 0;
	if (!(tmp_tab = ft_memalloc(sizeof(char *) * buf->argc)))
		return ;
	if (!(tmp_nbr = ft_memalloc(sizeof(int) * buf->argc)))
		return ;
	while (buf->tab_arg[++x] != NULL)
	{
		tmp_tab[x] = NULL;
		if (x != buf->pos)
		{
			tmp_tab[y] = ft_strdup(buf->tab_arg[x]);
			tmp_nbr[y] = buf->nbr[x];
			y++;
		}
		free(buf->tab_arg[x]);
	}
	free(buf->tab_arg);
	free(buf->nbr);
	struc_buf(buf, tmp_tab, tmp_nbr);
}
