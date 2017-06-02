/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 13:58:54 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/25 13:31:11 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_tab(char **tab)
{
	int		x;

	x = 0;
	while (tab[x] != NULL)
		x++;
	return (x);
}

static int	find_var(char *tmp_data, int x)
{
	char	*tmp_env;
	char	*p;

	tmp_env = ft_strdup(g_envp[x]);
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

static void	ft_remove(int x, int len_env)
{
	if (g_envp[0] != NULL && g_envp[1] == NULL)
	{
		free(g_envp[0]);
		free(g_envp);
		g_envp = NULL;
	}
	else
	{
		while (x < len_env)
		{
			free(g_envp[x]);
			if (g_envp[x + 1] != NULL)
				g_envp[x] = ft_strdup(g_envp[x + 1]);
			else
				g_envp[x] = NULL;
			x++;
		}
	}
	return ;
}

static void	ft_while_remove(char *data, int len_env)
{
	int		x;
	char	*tmp_data;

	x = 0;
	tmp_data = ft_strdup(data);
	while (g_envp[x] != NULL)
	{
		if ((find_var(tmp_data, x)) == 1)
			break ;
		x++;
	}
	free(tmp_data);
	if (g_envp[x] != NULL)
		ft_remove(x, len_env);
	return ;
}

void		remove_env(char *data)
{
	int		len_env;

	len_env = len_tab(g_envp);
	if (g_envp == NULL || data == NULL)
		return ;
	else
		return (ft_while_remove(data, len_env));
}
