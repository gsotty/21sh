/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 15:28:33 by gsotty            #+#    #+#             */
/*   Updated: 2019/04/04 14:14:31 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/built_int.h"
#include <stdio.h>

static void	free_tab(t_envp *my_envp)
{
	int		x;

	x = 0;
	if (my_envp->envp == NULL || my_envp->envp[0] == NULL)
		return ;
	while (my_envp->envp[x] != NULL)
	{
		free(my_envp->envp[x]);
		x++;
	}
	free(my_envp->envp);
}

int		env_argv(char **cmd, int ret, t_envp *my_envp)
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
			if (add_env(cmd[ret + y], p + 1, my_envp) == 1)
				return (1);
		}
		else
			break ;
		y++;
	}
	if (cmd[ret + y] != NULL)
	{
		exec_cmd(1, cmd + ret + y, my_envp->envp);
		y++;
	}
	else if (cmd[ret + y] == NULL)
	{
		cmd[0] = ft_strdup("env");
		cmd[1] = NULL;
		ft_env(cmd, my_envp);
	}
	return (0);
}

int		env_no_argv(t_envp *my_envp)
{
	int		x;

	x = 0;
	if (my_envp->envp == NULL || my_envp->envp[0] == NULL)
		return (1);
	while (my_envp->envp[x] != NULL)
	{
		write(1, my_envp->envp[x], ft_strlen(my_envp->envp[x]));
		write(1, "\n", 1);
		x++;
	}
	return (0);
}

int		ft_env(char **cmd, t_envp *my_envp)
{
	int				ret;
	t_flag_env		flag;

	ft_memset(&flag, '\0', sizeof(t_flag_env));
	if ((ret = check_flag_env(cmd, &flag, my_envp)) == -1)
		return (1);
	if (flag.i_min == 1)
	{
		free_tab(my_envp);
		my_envp->envp = NULL;
	}
	if (cmd[ret] == NULL && flag.u_min == 0)
	{
		if (env_no_argv(my_envp) == 1)
			return (1);
	}
	else
	{
		if (flag.u_min >= 1)
			remove_env(flag.name, my_envp);
		env_argv(cmd, ret, my_envp);
	}
	if (flag.u_min == 1)
		free(flag.name);
	return (0);
};
