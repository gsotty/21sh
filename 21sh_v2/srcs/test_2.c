/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 13:02:41 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/01 13:06:04 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../vingt_et_un_sh.h"

int			ft_strlen_t(char *str)
{
	int		x;

	x = 0;
	while (str[x] != '\0')
		x++;
	return (x);
}

int			main(int argc, char **argv)
{
	int		x;

	x = 0;
	while (x < argc)
	{
		write(1, argv[x], ft_strlen_t(argv[x]));
		write(1, "\n", 1);
		x++;
	}
}
