/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:18:51 by gsotty            #+#    #+#             */
/*   Updated: 2019/01/16 13:28:20 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/built_int.h"
#include <stdio.h>

int		ft_setenv(char **cmd, t_envp *my_envp)
{
	int		x;
	char	*p;

	x = 1;
	while (cmd[x] != NULL)
	{
		if (((p = ft_strchr(cmd[x], '=')) != NULL) && cmd[x][0] != '=')
		{
			*p = '\0';
			if (add_env(cmd[x], p + 1, my_envp) == 1)
				return (1);
		}
		else
		{
			printf("\033[31mminishell: setenv: \033[0m%s", cmd[x]);
			printf("\033[31m: invalid argument\n\033[0m");
			return (1);
		}
		x++;
	}
	return (0);
}
