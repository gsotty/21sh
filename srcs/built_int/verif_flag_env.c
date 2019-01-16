/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_flag_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 15:37:23 by gsotty            #+#    #+#             */
/*   Updated: 2019/01/16 13:53:21 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/built_int.h"
#include <stdio.h>

static int	ft_printf_erreur(char **cmd, int x, int y)
{
	printf("env: illegal option -- %c\nusage: env [-i] ",
			cmd[x][y]);
	printf("[-u name] [name=value ...]\n\t   [utility [argume");
	printf("nt ...]]\n");
	return (-1);
}

static int	verif_u_min(char **cmd, t_intflag *var, t_flag_env *flag,
		t_envp *my_envp)
{
	flag->u_min += 1;
	if (cmd[var->x][var->y + 1] != '\0')
	{
		flag->name = ft_strdup(cmd[var->x] + var->y + 1);
		remove_env(cmd[var->x] + var->y + 1, my_envp);
		return (1);
	}
	else if (cmd[var->x][var->y + 1] == '\0' && cmd[var->x + 1] != NULL)
	{
		flag->name = ft_strdup(cmd[var->x + 1]);
		remove_env(cmd[var->x + 1], my_envp);
		return (2);
	}
	else
	{
		printf("env: option requires an argument -- %c\nusage:",
				cmd[var->x][var->y]);
		printf(" env [-i] [-u name] [name=value ...]");
		printf("\n\t   [utility [argument ...]]\n");
		exit(0);
	}
}

static int	verif_flag_env(char **cmd, t_intflag *var, t_flag_env *flag,
		t_envp *my_envp)
{
	var->y = 1;
	if (cmd[var->x][0] == '-' && cmd[var->x][1] != '\0')
	{
		while (cmd[var->x][var->y] != '\0')
		{
			if (cmd[var->x][var->y] == 'i')
				flag->i_min = 1;
			else if (cmd[var->x][var->y] == 'u')
				return (verif_u_min(cmd, var, flag, my_envp));
			else
				return (ft_printf_erreur(cmd, var->x, var->y));
			var->y++;
		}
		return (1);
	}
	else if (cmd[var->x][0] == '-' && cmd[var->x][1] == '\0')
		flag->i_min = 1;
	else
		return (0);
	return (1);
}

int			check_flag_env(char **cmd, t_flag_env *flag, t_envp *my_envp)
{
	int			ret;
	t_intflag	var;

	ft_memset(&var, '\0', sizeof(var));
	var.x = 1;
	while (cmd[var.x] != NULL)
	{
		if ((ret = verif_flag_env(cmd, &var, flag, my_envp)) == 0)
			break ;
		if (ret == -1)
			return (-1);
		if (ret == 2)
			var.x++;
		var.x++;
	}
	return (var.x);
}
