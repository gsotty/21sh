/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:49:00 by gsotty            #+#    #+#             */
/*   Updated: 2019/01/16 14:09:03 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/built_int.h"

int		ft_unsetenv(char **cmd, t_envp *my_envp)
{
	int		x;

	x = 1;
	while (cmd[x] != NULL)
	{
		remove_env(cmd[x], my_envp);
		x++;
	}
	return (1);
}
