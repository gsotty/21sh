/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 12:58:10 by gsotty            #+#    #+#             */
/*   Updated: 2019/01/16 14:19:44 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/built_int.h"

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
		write(1, argv[x], ft_strlen(argv[x]));
		if (argv[x + 1] != NULL)
			write(1, " ", 1);
		x++;
	}
}

static void	no_flag_n(char **argv)
{
	int		x;

	x = 1;
	while (argv[x] != NULL)
	{
		write(1, argv[x], ft_strlen(argv[x]));
		if (argv[x + 1] != NULL)
			write(1, " ", 1);
		x++;
	}
	write(1, "\n", 1);
}

int			ft_echo(char **argv, t_envp *my_envp)
{
	(void)my_envp;
	if (check_flag_echo(argv) == 1)
		flag_n(argv);
	else
		no_flag_n(argv);
	return (0);
}
