/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:18:51 by gsotty            #+#    #+#             */
/*   Updated: 2017/06/02 10:20:14 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

void	ft_setenv(char **cmd, char ***envp)
{
	int		x;

	x = 1;
	while (cmd[x] != NULL)
	{
		if (ft_strchr(cmd[x], '=') != NULL && cmd[x][0] != '=')
			add_env(cmd[x], envp);
		else
		{
			write(2, ft_strjoin("\033[31mminishell: setenv: \033[0m", cmd[x]),
					ft_strlen(cmd[x]) + 31);
			write(2, "\033[31m: invalid argument\n\033[0m", 32);
			return ;
		}
		x++;
	}
	return ;
}
