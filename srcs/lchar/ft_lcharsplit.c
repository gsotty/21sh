/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lcharsplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:53:16 by gsotty            #+#    #+#             */
/*   Updated: 2019/04/04 15:23:46 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int				ft_lcharmatch(t_lchar *buf, int start, char **token)
{
	int			x;
	int			tx;
	int			is_space;

	is_space = 0;
	x = 0;
	while (buf->type[x + start] == _SPACE || buf->type[x + start] == _NEW_LINE)
	{
		is_space = 1;
		x++;
	}
	if (is_space == 1)
		return (x);
	tx = 0;
	while (token[tx] != NULL)
	{
		x = 0;
		while ((token[tx][x] != '\0' && (x + start < buf->len) &&
					buf->type[x + start] == (int)token[tx][x]))
			x++;
		if (token[tx][x] == '\0')
			return (x);
		tx++;
	}
	return (-1);
}

int				ft_nbrlcharsplit(int count, int start, t_lchar *buf,
		char **token)
{
	int			ret;
	int			nbr_tab;

	nbr_tab = 0;
	while (count < buf->len)
	{
		if ((ret = ft_lcharmatch(buf, count, token)) > -1)
		{
			if (count != start)
			{
				nbr_tab++;
				start = count;
			}
			nbr_tab++;
			if ((count = count + ret) >= buf->len)
				return (nbr_tab);
			start = count;
		}
		else
			count++;
	}
	nbr_tab++;
	return (nbr_tab);
}

int				ft_splitbuf(int count, t_lchar **tab, t_lchar *buf,
		char **token)
{
	int			ret;
	int			nbr_tab;
	int			start;

	start = 0;
	nbr_tab = 0;
	while (count < buf->len)
	{
		if ((ret = ft_lcharmatch(buf, count, token)) > -1)
		{
			if (count != start)
			{
				tab[nbr_tab++] = ft_lcharndup(buf, start, count - 1);
				start = count;
			}
			tab[nbr_tab++] = ft_lcharndup(buf, start, count + (ret - 1));
			if ((count = count + ret) >= buf->len)
				return (0);
			start = count;
		}
		else
			count++;
	}
	tab[nbr_tab++] = ft_lcharndup(buf, start, count - 1);
	return (0);
}

t_lchar			**ft_lcharsplit(t_lchar *buf, char **token)
{
	int			len_tab;
	t_lchar		**tab;

	len_tab = ft_nbrlcharsplit(0, 0, buf, token);
	if ((tab = ft_memalloc(sizeof(t_lchar *) * (len_tab + 1))) == NULL)
		return (NULL);
	ft_splitbuf(0, tab, buf, token);
	return (tab);
}
