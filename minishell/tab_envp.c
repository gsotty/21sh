/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 12:45:18 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/25 16:56:00 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**creat_env(char **envp_begin)
{
	int		x;

	x = 0;
	if (envp_begin == NULL || envp_begin[0] == NULL)
		return (NULL);
	while (envp_begin[x] != NULL)
		x++;
	if ((g_envp = ft_memalloc(sizeof(char *) * (x + 1))) == NULL)
		return (NULL);
	x = 0;
	while (envp_begin[x] != NULL)
	{
		g_envp[x] = ft_strdup(envp_begin[x]);
		x++;
	}
	return (g_envp);
}

void	remalloc_env_2(int after_size, int new_size, char **new_env)
{
	int		x;

	free(g_envp);
	if ((g_envp = ft_memalloc(sizeof(char *) * (new_size + 1))) == NULL)
		return ;
	x = 0;
	while (x < after_size)
	{
		g_envp[x] = ft_strdup(new_env[x]);
		free(new_env[x]);
		new_env[x] = NULL;
		x++;
	}
	free(new_env);
	return ;
}

void	remalloc_env(int after_size, int new_size)
{
	int		x;
	char	**new_env;

	if ((new_env = ft_memalloc(sizeof(char *) * (new_size + 1))) == NULL)
		return ;
	x = 0;
	while (x < after_size)
	{
		new_env[x] = ft_strdup(g_envp[x]);
		free(g_envp[x]);
		g_envp[x] = NULL;
		x++;
	}
	remalloc_env_2(after_size, new_size, new_env);
}
