/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 16:44:31 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/29 16:45:37 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static int		is_char(char str, char *c)
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

static void		ft_while(char **tab_2, char const *buf, char *c, t_split *len)
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
	if (!(tab_2[len->x] = ft_memalloc(sizeof(**tab_2) * ((fin - debut) + 1))))
		return ;
	ft_memcpy(tab_2[len->x], buf + len->j + debut, fin - debut);
	tab_2[len->x][fin - debut] = '\0';
	len->j += fin;
}

char			**ft_strsplit_space(char const *buf, char *c)
{
	t_split		len;
	char		**tab_2;

	tab_2 = NULL;
	ft_memset(&len, 0, sizeof(t_split));
	if ((tab_2 = ft_memalloc(sizeof(*tab_2) * (MAX_CANON))) == NULL)
		return (NULL);
	while (buf[len.j] != '\0' && len.x < MAX_CANON)
	{
		ft_while(tab_2, buf, c, &len);
		while (is_char(buf[len.j], c) == 1 && buf[len.j] != '\0')
			len.j++;
		len.x++;
	}
	if (len.x > MAX_CANON)
	{
		write(2, "21sh: command too long:", 23);
		return (NULL);
	}
	return (tab_2);
}
