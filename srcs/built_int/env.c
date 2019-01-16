/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 15:28:33 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/03 10:26:23 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/built_int.h"
#include <stdio.h>

static void	free_tab(char **tab)
{
	int		x;

	x = 0;
	if (tab == NULL || tab[0] == NULL)
		return ;
	while (tab[x] != NULL)
	{
		free(tab[x]);
		x++;
	}
	if (tab != NULL)
		free(tab);
}

void	env_argv(char **cmd, int ret, char ***envp)
{
	int		y;
	char	*p;

	y = 0;
	while (cmd[ret + y] != NULL)
	{
		if (((p = ft_strchr(cmd[ret + y], '=')) != NULL) &&
				cmd[ret + y][0] != '=')
		{
			*p = '\0';
			add_env(cmd[ret + y], p + 1, envp);
		}
		else
			break ;
		y++;
	}
	if (cmd[ret + y] != NULL)
	{
		exec_cmd(1, cmd + ret + y, *envp);
		y++;
	}
	else if (cmd[ret + y] == NULL)
	{
		cmd[0] = ft_strdup("env");
		cmd[1] = NULL;
		ft_env(cmd, envp);
	}
	return ;
}

void	env_no_argv(char **envp)
{
	int		x;

	x = 0;
	if (envp == NULL || envp[0] == NULL)
		return ;
	while (envp[x] != NULL)
	{
		write(1, envp[x], ft_strlen(envp[x]));
		write(1, "\n", 1);
		x++;
	}
	return ;
}

void	ft_env(char **cmd, char ***envp)
{
	int				ret;
	t_flag_env		flag;

	ft_memset(&flag, '\0', sizeof(t_flag_env));
	if ((ret = check_flag_env(cmd, &flag, envp)) == -1)
		return ;
	if (flag.i_min == 1)
	{
		free_tab(*envp);
		*envp = NULL;
	}
	if (cmd[ret] == NULL && flag.u_min == 0)
		env_no_argv(*envp);
	else
	{
		if (flag.u_min >= 1)
			remove_env(flag.name, envp);
		env_argv(cmd, ret, envp);
	}
	if (flag.u_min == 1)
		free(flag.name);
	return ;
}
