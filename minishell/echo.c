/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 12:58:10 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/31 14:10:42 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_flag_echo(char **argv)
{
	if (argv[1] != NULL)
		if (argv[1][0] == '-' && argv[1][1] == 'n' && argv[1][2] == '\0')
			return (1);
	return (0);
}

static void	flag_n(char **argv)
{
	int		x;

	x = 2;
	while (argv[x] != NULL)
	{
		if (argv[x + 1] != NULL)
			ft_printf("%s ", argv[x]);
		else
			ft_printf("%s", argv[x]);
		x++;
	}
}

static void	no_flag_n(char **argv)
{
	int		x;

	x = 1;
	while (argv[x] != NULL)
	{
		if (argv[x + 1] != NULL)
			ft_printf("%s ", argv[x]);
		else
			ft_printf("%s", argv[x]);
		x++;
	}
	write(1, "\n", 1);
}

int			echo(char **argv)
{
	if (check_flag_echo(argv) == 1)
		flag_n(argv);
	else
		no_flag_n(argv);
	return (0);
}
