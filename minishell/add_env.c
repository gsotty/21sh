/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 15:34:40 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/03 10:18:41 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_var(char *tmp_data)
{
	int		x;
	char	*p;
	char	*tmp_env;

	x = 0;
	if (g_envp == NULL || g_envp[0] == NULL)
		return (0);
	while (g_envp[x] != NULL)
	{
		tmp_env = ft_strdup(g_envp[x]);
		p = ft_strchr(tmp_env, '=');
		*p = 0;
		if (ft_strcmp(tmp_env, tmp_data) == 0)
		{
			free(tmp_env);
			break ;
		}
		free(tmp_env);
		x++;
	}
	return (x);
}

static void	envp_null(char *data)
{
	if (g_envp == NULL)
	{
		if ((g_envp = ft_memalloc(sizeof(char *) * 2)) == NULL)
			return ;
		g_envp[0] = ft_strdup(data);
	}
	else
		g_envp[0] = ft_strdup(data);
	return ;
}

void		envp_no_null(char *data)
{
	int		x;
	char	*p;
	char	*tmp_data;

	if ((tmp_data = ft_strdup(data)) == NULL)
		return ;
	p = ft_strchr(tmp_data, '=');
	*p = '\0';
	x = find_var(tmp_data);
	if (g_envp[x] == NULL)
	{
		remalloc_env(x, x + 1);
		g_envp[x] = ft_strdup(data);
	}
	else
	{
		free(g_envp[x]);
		g_envp[x] = ft_strdup(data);
	}
	free(tmp_data);
	return ;
}

void		add_env(char *data)
{
	if (g_envp == NULL || g_envp[0] == NULL)
	{
		envp_null(data);
		return ;
	}
	else
		envp_no_null(data);
	return ;
}
