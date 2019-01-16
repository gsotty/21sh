/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 13:58:54 by gsotty            #+#    #+#             */
/*   Updated: 2019/01/16 13:17:52 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/built_int.h"

static int	find_var(char *tmp_data, int x, t_envp *my_envp)
{
	char	*tmp_env;
	char	*p;

	tmp_env = ft_strdup(my_envp->envp[x]);
	p = ft_strchr(tmp_env, '=');
	*p = '\0';
	if (ft_strcmp(tmp_env, tmp_data) == 0)
	{
		free(tmp_env);
		return (1);
	}
	free(tmp_env);
	return (0);
}

static int	ft_remove(int x, t_envp *my_envp)
{
	if (my_envp->len == 1)
	{
		free(my_envp->envp[0]);
		free(my_envp->envp);
		my_envp->envp = NULL;
	}
	else
	{
		while (x < my_envp->len)
		{
			free(my_envp->envp[x]);
			if (my_envp->envp[x + 1] != NULL)
				my_envp->envp[x] = ft_strdup(my_envp->envp[x + 1]);
			else
				my_envp->envp[x] = NULL;
			x++;
		}
	}
	return (0);
}

static int	ft_while_remove(char *data, t_envp *my_envp)
{
	int		x;
	char	*tmp_data;

	x = 0;
	tmp_data = ft_strdup(data);
	while (my_envp->envp[x] != NULL)
	{
		if ((find_var(tmp_data, x, my_envp)) == 1)
			break ;
		x++;
	}
	free(tmp_data);
	if (my_envp->envp[x] != NULL)
		ft_remove(x, my_envp);
	return (0);
}

int			remove_env(char *data, t_envp *my_envp)
{
	if (my_envp->envp == NULL || data == NULL)
		return (1);
	else
		return (ft_while_remove(data, my_envp));
}
