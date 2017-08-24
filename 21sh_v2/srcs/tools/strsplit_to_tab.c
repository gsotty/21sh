/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsplit_to_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 10:43:47 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/24 14:17:15 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int		count_split(char *cmd, const char *c)
{
	int		x;
	int		y;
	int		count;

	x = 0;
	count = 0;
	while (cmd[x] != '\0')
	{
		y = 0;
		while (c[y] != '\0')
		{
			if (c[y] == cmd[x])
				count++;
			y++;
		}
		x++;
	}
	return (count);
}

int		count_split_cmd(char **cmd_tab, const char *c)
{
	int		x;
	int		y;
	int		z;
	int		count;

	x = 0;
	count = 0;
	while (cmd_tab[x] != NULL)
	{
		y = 0;
		while (cmd_tab[x][y] != '\0')
		{
			z = 0;
			while (c[z] != '\0')
			{
				if (cmd_tab[x][y] == c[z])
				{
					if (y == 0)
						count = x;
					else
						count = x;
					return (count);
				}
				z++;
			}
			y++;
		}
		x++;
	}
	count = x;
	return (count);
}

char	*argc_to_pipe(char *cmd)
{
	int		x;
	int		len_cmd;
	char	*new;

	x = 0;
	len_cmd = ft_strlen(cmd);
	while (cmd[x] != '\0')
	{
		if (cmd[x] == '|')
			break;
		x++;
	}
	if ((new = ft_memalloc(sizeof(char *) * (x + 1))) == NULL)
		return (NULL);
	ft_memcpy(new, cmd, x);
	new[x] = '\0';
	ft_printf("%s, %s\n", new, cmd);
	ft_memmove(cmd, cmd + x + 1, len_cmd - (x + 1));
	cmd[len_cmd - (x + 1)] = '\0';
	ft_printf("%s\n", cmd);
	return (new);
}

char	***strsplit_to_tab(int len_cmd, char **cmd_tab, const char *c)
{
	int		x;
	int		y;
	int		count;
	int		nbr_split;
	char	***new_tab;

	x = 0;
	new_tab = NULL;
	nbr_split = 1;
	(void)len_cmd;
	while (cmd_tab[x] != NULL)
	{
		nbr_split += count_split(cmd_tab[x], c);
		x++;
	}
	ft_printf("%d\n", nbr_split);
	if ((new_tab = ft_memalloc(sizeof(char **) * (nbr_split + 1))) == NULL)
		return (NULL);
	x = 0;
	count = 0;
	while (x < nbr_split)
	{
		y = 0;
		ft_printf("c'est le %d, %d\n", x, count = (count_split_cmd(cmd_tab, "|")));
		if ((new_tab[x] = ft_memalloc(sizeof(char *) * (count + 1))) == NULL)
			return (NULL);
		while (y < count)
		{
			ft_printf("copie: %s\n", cmd_tab[y]);
			new_tab[x][y] = ft_strdup(cmd_tab[y]);
			y++;
		}
		ft_printf("(%s)\n", cmd_tab[0]);
		if (cmd_tab[y] != NULL)
		{
			ft_printf("(%s)\n", cmd_tab[y]);
			if (cmd_tab[y][0] == '|' && cmd_tab[y][1] == '\0')
				cmd_tab = cmd_tab + (y + 1);
			else if (cmd_tab[y][0] != '|')
			{
				new_tab[x][y] = argc_to_pipe(cmd_tab[y]);
				cmd_tab = cmd_tab + y;
				y++;
			}
			ft_printf("(%s)\n", cmd_tab[0]);
		}
		new_tab[x][y] = NULL;
		x++;
	}
	new_tab[x] = NULL;
	ft_printf("test:\n");
	x = 0;
	while (new_tab[x] != NULL)
	{
		y = 0;
		ft_printf("argc: %d\n", x);
		while (new_tab[x][y] != NULL)
		{
			ft_printf("%s\n", new_tab[x][y]);
			y++;
		}
		x++;
	}
	return (new_tab);
}
