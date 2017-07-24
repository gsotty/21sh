/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 15:59:07 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/10 17:52:45 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_char(char str, char *c)
{
	int		x;

	x = 0;
	while (c[x] != '\0')
	{
		if (c[x] == str)
			return (1);
		x++;
	}
	return (0);
}

void	ft_while(char **tab, char const *buf, char *c, t_split *len)
{
	int		y;
	int		fin;
	int		debut;

	y = 0;
	fin = 0;
	debut = 0;
	while (is_char(buf[y + len->j], c) == 1 && buf[y + len->j] != '\0')
		y++;
	debut = y;
	while (is_char(buf[y + len->j], c) == 0 && buf[y + len->j] != '\0')
		y++;
	fin = y;
	if (!(tab[len->x] = ft_memalloc(sizeof(**tab) * ((fin - debut) + 1))))
		return ;
	ft_memcpy(tab[len->x], buf + len->j + debut, fin - debut);
	tab[len->x][fin - debut] = '\0';
	len->j += fin;
}

char	**ft_strsplit_space(char const *buf, char *c)
{
	t_split		len;
	char		**tab;

	tab = NULL;
	ft_memset(&len, 0, sizeof(t_split));
	if ((tab = ft_memalloc(sizeof(*tab) * (MAX_CANON))) == NULL)
		return (NULL);
	while (buf[len.j] != '\0' && len.x < MAX_CANON)
	{
		ft_while(tab, buf, c, &len);
		while (is_char(buf[len.j], c) == 1 && buf[len.j] != '\0')
			len.j++;
		len.x++;
	}
	return (tab);
}
